#include "StdAfx.h"
#include "misPanoramicTextureGenerator.h"

#include "misMathUtils.h"
#include "misParametricSpline.h"
#include "misDebug.h"


misPanoramicTextureGenerator::misPanoramicTextureGenerator(
	const std::vector<PointType>& points, double dS, double dN, double intervalN, const double& imageWidth,
	const double& imageHeight, double precision, std::shared_ptr<Injector> injector /*= nullptr*/ )
	: m_StepSizeAlongCurveNormal(dN), m_StepSizeAlongCurveTangent(dS), m_CurveDisplacementRange(intervalN), 
	m_ImageWidth(imageWidth), m_ImageHeight(imageHeight), m_LengthPrecision(precision), m_Injector(injector)
{
	if (!m_Injector)
		m_Injector = std::make_shared<Injector>();

	m_OriginalCurveSpline = injector->CreateParametricSpline(points, m_LengthPrecision);
	const int ChannelSize = 4, TextureDepth = 1;
	int numberOfSamplesAlongCurveTangent, numberOfSamplesAlongCurveNormal;
	FindNumOfSamples();
	m_PanoramicToImageTexture = std::make_shared<TextureData>(
		m_NumberOfSamplesAlongCurveTangent, m_NumberOfSamplesAlongCurveNormal, TextureDepth, ChannelSize);
}

std::shared_ptr<ITextureGenerator::TextureData> misPanoramicTextureGenerator::GetPanoramicTexture() const 
{
	const int ChannelSize = 4;
  	for(auto i = 0; i < m_NumberOfSamplesAlongCurveNormal; i++)
  	{
  		auto coordN = i * m_StepSizeAlongCurveNormal - m_CurveDisplacementRange;
  		auto displacedSpline = m_OriginalCurveSpline->GetDisplacedSpline(coordN);
		auto displacedSplineLength  = displacedSpline->GetLength();
		auto stepSizeAlongDisplacedSpline = displacedSplineLength / m_NumberOfSamplesAlongCurveTangent;
		auto paramMax = displacedSpline->GetMaxParameter(), paramMin = displacedSpline->GetMinParameter();
		auto parameterStepSize = (paramMax - paramMin) * m_LengthPrecision / displacedSplineLength;
		auto coordS = 0.0;
		auto previousPoint = displacedSpline->EvaluateAt(paramMin);
		int indexJ = 0, indexJPrev = 0;
		double minDistPrev = stepSizeAlongDisplacedSpline;
		for (auto sp = paramMin; sp < paramMax; sp += parameterStepSize)
		{
			auto currentPoint = displacedSpline->EvaluateAt(sp);
			coordS += (currentPoint - previousPoint).GetNorm();
			previousPoint = currentPoint;
			auto indexJ = static_cast<int>(coordS / stepSizeAlongDisplacedSpline);
			if(indexJPrev != indexJ)
			{
				minDistPrev = stepSizeAlongDisplacedSpline;
				indexJPrev = indexJ;
			}
			auto modulus = std::fmod(coordS, stepSizeAlongDisplacedSpline);
			if( minDistPrev < modulus)
				continue;
			int elementIndex = ChannelSize * (indexJ + i * m_NumberOfSamplesAlongCurveTangent);
			FillTextureElements( elementIndex, currentPoint);
			minDistPrev = modulus;	
		}
  	}
 	return m_PanoramicToImageTexture;
}

void misPanoramicTextureGenerator::FillTextureElements( int elementIndex, const itk::Point<double, 3> point ) const
{
	m_PanoramicToImageTexture->Data[elementIndex] = 
		static_cast<TextureDataType>(point[0]) / static_cast<TextureDataType>(m_ImageWidth);
	m_PanoramicToImageTexture->Data[elementIndex + 1] = 
		static_cast<TextureDataType>(point[1]) / static_cast<TextureDataType>(m_ImageHeight);
	m_PanoramicToImageTexture->Data[elementIndex + 2] = 0.0;
	m_PanoramicToImageTexture->Data[elementIndex + 3] = 1.0;
}

void misPanoramicTextureGenerator::FindNumOfSamples() 
{
	const int ExpansionDirections = 2, ForTheOriginalCurve = 1;
	auto splineLength = m_OriginalCurveSpline->GetLength();
	m_NumberOfSamplesAlongCurveTangent = static_cast<int>(splineLength / m_StepSizeAlongCurveTangent);
	m_NumberOfSamplesAlongCurveNormal = 
		static_cast<int>(ExpansionDirections * m_CurveDisplacementRange / m_StepSizeAlongCurveNormal) + ForTheOriginalCurve;
}

std::shared_ptr<IParametricSpline> misPanoramicTextureGenerator::Injector::CreateParametricSpline( 
	std::vector<PointType> splinePoints, double precision ) const
{
	return std::make_shared<misParametricSpline>(splinePoints, precision);
}

