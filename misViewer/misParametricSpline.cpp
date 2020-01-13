#include "StdAfx.h"
#include "misParametricSpline.h"
#include "misMathUtils.h"


misParametricSpline::misParametricSpline(const std::vector<PointType>& inputPointSet, double precision)
	: m_ParametricSpline(vtkSmartPointer<vtkParametricSpline>::New()), m_Precision(precision),
	CoarseLengthComputationStepSize(0.1)
{
	auto points = vtkSmartPointer<vtkPoints>::New();
	for (auto pointItr = inputPointSet.cbegin(); pointItr != inputPointSet.cend(); ++pointItr)
		points->InsertNextPoint(pointItr->GetDataPointer());

	m_ParametricSpline->SetPoints(points);

	m_CoarseLength = ComputeLength(
		m_ParametricSpline->GetMinimumU(), m_ParametricSpline->GetMaximumU(), CoarseLengthComputationStepSize);
	m_StepSize = ComputeStepSize();
}

itk::Point<double, 3> misParametricSpline::EvaluateAt(double splineParameter) const
{
	double u[3], pt[3], du[9];
	u[0] = splineParameter;
	m_ParametricSpline->Evaluate(u, pt, du);
	return itk::Point<double, 3>(pt);
}

double misParametricSpline::GetLength() const
{
	return GetPartialLength(m_ParametricSpline->GetMinimumU(), m_ParametricSpline->GetMaximumU());
}

double misParametricSpline::GetPartialLength(double minVal, double maxVal) const
{
	return ComputeLength(minVal, maxVal, m_StepSize);
}

double misParametricSpline::GetSplineParamByPartialLength(double length) const
{
	auto minVal = m_ParametricSpline->GetMinimumU();
	return GetSplineParamByPartialLength(length, minVal);
}

double misParametricSpline::GetSplineParamByPartialLength(double length, double minVal) const 
{
	auto maxVal = m_ParametricSpline->GetMaximumU();
	double lengthSum = 0;
	auto prevPoint = EvaluateAt(minVal);
	for (double splineParam = minVal; splineParam < maxVal; splineParam += m_StepSize)
	{
		auto currentPoint = EvaluateAt(splineParam);
		lengthSum += (currentPoint - prevPoint).GetNorm();
		if (lengthSum > length)
			return splineParam;
		prevPoint = currentPoint;
	}
	return maxVal;
}

itk::Vector<double, 3> misParametricSpline::ComputeNormalVecAt(double splineParam) const 
{
	double zPUnitCoords[] = { 0, 0, -1 };
	return itk::CrossProduct(ComputeTangentialVecAt(splineParam), zPUnitCoords);
}

itk::Vector<double, 3> misParametricSpline::ComputeTangentialVecAt(double splineParam) const
{
	const double DifferentiationPrecisionFactor = 1e-3;
	double splineParamDiff = m_StepSize * DifferentiationPrecisionFactor;

	if (splineParam + splineParamDiff > GetMaxParameter())
		splineParam = GetMaxParameter() - splineParamDiff;
	else if (splineParam - splineParamDiff < GetMinParameter())
		splineParam = GetMinParameter() + splineParamDiff;
	auto point1 = EvaluateAt(splineParam - splineParamDiff);
	auto point2 = EvaluateAt(splineParam + splineParamDiff);
	auto tangentialUnitVector = point2 - point1;
	tangentialUnitVector[2] = 0;
	tangentialUnitVector.Normalize();
	return tangentialUnitVector;
}
 
std::shared_ptr<IParametricSpline> misParametricSpline::GetDisplacedSpline(double displacementSize) const
{
	std::vector<PointType> displacedPoints;
	auto minParam = m_ParametricSpline->GetMinimumU(), maxParam = m_ParametricSpline->GetMaximumU();
	const int NumberOfSeedPointsPerOriginalSplinePoint = 3;
	auto numberOfPoints = 
		m_ParametricSpline->GetPoints()->GetNumberOfPoints() * NumberOfSeedPointsPerOriginalSplinePoint;
	auto stepSizeAlongCurveTangent = (maxParam - minParam) / numberOfPoints;

	for (double s = minParam; s < maxParam; s += stepSizeAlongCurveTangent)
		displacedPoints.push_back(DisplacePointAlongNormal(s, displacementSize));

	displacedPoints.push_back(DisplacePointAlongNormal(maxParam, displacementSize));

	return std::make_shared<misParametricSpline>(displacedPoints, m_Precision);
}

misParametricSpline::PointType misParametricSpline::DisplacePointAlongNormal(double s, double displacementSize) const
{
	auto initialPoint = EvaluateAt(s);
	auto normalVectorOfCurve = ComputeNormalVecAt(s);
	PointType displacedPoint = initialPoint + normalVectorOfCurve * displacementSize;
	return displacedPoint;
}

double misParametricSpline::GetMinParameter() const
{
	return m_ParametricSpline->GetMinimumU();
}

double misParametricSpline::GetMaxParameter() const
{
	return m_ParametricSpline->GetMaximumU();
}

double misParametricSpline::ComputeStepSize() const
{
	const double SafetyFactor = 0.7;
	auto minVal = m_ParametricSpline->GetMinimumU(), maxVal = m_ParametricSpline->GetMaximumU();
	return (maxVal - minVal) * m_Precision / m_CoarseLength * SafetyFactor;
}

double misParametricSpline::ComputeLength(double minVal, double maxVal, double stepSize) const
{
	double length = 0;
	auto prevPoint = EvaluateAt(minVal);
	double partialStepSize = (maxVal - minVal) * stepSize;

	for (double splineParam = minVal; splineParam < maxVal; splineParam += partialStepSize)
	{
		auto currentPoint = EvaluateAt(splineParam);
		length += (currentPoint - prevPoint).GetNorm();
		prevPoint = currentPoint;
	}

	auto currentPoint = EvaluateAt(maxVal);
	length += (currentPoint - prevPoint).GetNorm();
	return length;
}