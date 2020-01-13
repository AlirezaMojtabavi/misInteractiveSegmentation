#include "StdAfx.h"
#include "misPanoramicCoordinatesConverter.h"
#include "misParametricSpline.h"

misPanoramicCoordinatesConverter::misPanoramicCoordinatesConverter(const std::vector<PointType>& panoramicCurvePoints, 
	double imageDimZ, double precision, std::shared_ptr<Injector> m_Injector /*= nullptr*/)
	: NumberOfSplineDivisionsPerSplinedPoint(5), NumberOfSplineDivisionsPerSubsequentPass(5),
	m_Precision(precision), m_ImageDimensionZ(imageDimZ)
{
	if (!m_Injector)
		m_Injector = std::make_shared<Injector>();
	m_OriginalCurveSpline = m_Injector->CreateParametricSpline(panoramicCurvePoints, precision);
	m_InitialNumberOfSplineDivisions = static_cast<int>(panoramicCurvePoints.size()) * NumberOfSplineDivisionsPerSplinedPoint;
	SetPanoramicCoordinates(0, 0, 0);
}

void misPanoramicCoordinatesConverter::SetImageCoordinates( double x, double y, double z )
{
	m_ImageX = x;
	m_ImageY = y;
	m_ImageZ = z;
	double imageCoords[] = { m_ImageX, m_ImageY, 0 };
	PointType imagePoint(imageCoords);
	auto closestSp = FindClosestPointOnSpline(m_OriginalCurveSpline, imagePoint);
	auto pointProjectionOnSpline = m_OriginalCurveSpline->EvaluateAt(closestSp);
	auto normalVector = imagePoint - pointProjectionOnSpline;
	auto normalUnitVector = m_OriginalCurveSpline->ComputeNormalVecAt(closestSp);
	m_PanoramicN = normalUnitVector * normalVector;
	m_DisplacedSpline = m_OriginalCurveSpline->GetDisplacedSpline(m_PanoramicN);
	auto closestSParamOnDisplacedSpline = FindClosestPointOnSpline(m_DisplacedSpline, imagePoint);
	m_PanoramicS = m_DisplacedSpline->GetPartialLength(m_DisplacedSpline->GetMinParameter(), closestSParamOnDisplacedSpline);
	m_PanoramicZp = m_ImageDimensionZ - m_ImageZ;
}

void misPanoramicCoordinatesConverter::GetImageCoordinates( double &x, double &y, double &z ) const
{
	x = m_ImageX;
	y = m_ImageY;
	z = m_ImageZ;
}

void misPanoramicCoordinatesConverter::SetPanoramicCoordinates( double s, double z_p, double n )
{
	m_PanoramicS = s;
	m_PanoramicN = n;
	m_PanoramicZp = z_p;
	m_DisplacedSpline = m_OriginalCurveSpline->GetDisplacedSpline(m_PanoramicN);
	auto splineParam  = m_DisplacedSpline->GetSplineParamByPartialLength(m_PanoramicS);
	auto imagePoint = m_DisplacedSpline->EvaluateAt(splineParam);
	m_ImageX = imagePoint[0];
	m_ImageY = imagePoint[1];
	m_ImageZ = m_ImageDimensionZ - m_PanoramicZp;
}

void misPanoramicCoordinatesConverter::GetPanoramicCoordinates( double &s, double &z_p, double &n ) const
{
	n = m_PanoramicN;
	s = m_PanoramicS;
	z_p = m_PanoramicZp;
}

double misPanoramicCoordinatesConverter::GetCurrentSplineLength() const 
{
	return m_DisplacedSpline->GetLength();
}

misPanoramicCoordinatesConverter::VectorType misPanoramicCoordinatesConverter::GetCurrentNormalVector() const 
{
	auto sp = m_DisplacedSpline->GetSplineParamByPartialLength(m_PanoramicS);
	return m_DisplacedSpline->ComputeNormalVecAt(sp);
}

misPanoramicCoordinatesConverter::VectorType misPanoramicCoordinatesConverter::GetCurrentTangentialVector() const
{
	auto sp = m_DisplacedSpline->GetSplineParamByPartialLength(m_PanoramicS);
	return m_DisplacedSpline->ComputeTangentialVecAt(sp);
}

IPanoramicCoordinatesConverter::PointType misPanoramicCoordinatesConverter::EvaluateCurrentSpline(double s) const
{
	auto splineParam = m_DisplacedSpline->GetSplineParamByPartialLength(s);
	auto imagePoint = m_DisplacedSpline->EvaluateAt(splineParam);
	imagePoint[2] = m_ImageDimensionZ - m_PanoramicZp;
	return imagePoint;
}

double misPanoramicCoordinatesConverter::MinimizeExpressionToFindSplineParam(
	std::shared_ptr<IParametricSpline>spline, std::function<double (double sP)> expression) const
{
	double closestSpStart = spline->GetMinParameter(), 
		closestSpEnd = spline->GetMaxParameter();
	double splineFragmentLength;
	auto performPass = [&](int numberOfSplineDivision)
	{
		MinimizeExpressionToNarrowParamRange(numberOfSplineDivision, closestSpStart, closestSpEnd, expression);
		splineFragmentLength = spline->GetPartialLength(closestSpStart, closestSpEnd);
	};

	performPass(m_InitialNumberOfSplineDivisions);
	while (splineFragmentLength > m_Precision)
		performPass(NumberOfSplineDivisionsPerSubsequentPass);

	auto closesSp = (closestSpStart + closestSpEnd) / 2;
	closesSp = std::min(spline->GetMaxParameter(), std::max(spline->GetMinParameter(), closesSp));
	return closesSp;
}

void misPanoramicCoordinatesConverter::MinimizeExpressionToNarrowParamRange(
	int divisions, double& start, double& end, std::function<double (double sP)> expression ) const
{
	auto stepSize = (end - start) / divisions;
	double closestSp = start, closestDistance = expression(start);
	for (double sP = start; sP < end; sP += stepSize)
	{
		auto dist = expression(sP);
		if (dist < closestDistance)
		{
			closestDistance = dist;
			closestSp = sP;
		}
	}
	start = closestSp - stepSize;
	end = closestSp + stepSize;
}

void misPanoramicCoordinatesConverter::SetPanoramicSPrecision( double precision )
{
	m_Precision = std::abs(precision);
}

double misPanoramicCoordinatesConverter::FindClosestPointOnSpline(
	std::shared_ptr<IParametricSpline> spline, const PointType& toPoint) const
{
	auto findDistanceToPoint = [&] (double sP) -> double
	{
		auto splinePoint = spline->EvaluateAt(sP);
		auto distanceVector = splinePoint - toPoint;
		distanceVector[2] = 0;
		return distanceVector.GetNorm();
	};
	return MinimizeExpressionToFindSplineParam(spline, findDistanceToPoint);
}

std::shared_ptr<IParametricSpline> misPanoramicCoordinatesConverter::Injector::CreateParametricSpline( 
	std::vector<PointType> splinePoints, double precision ) const
{
	return std::make_shared<misParametricSpline>(splinePoints, precision);
}