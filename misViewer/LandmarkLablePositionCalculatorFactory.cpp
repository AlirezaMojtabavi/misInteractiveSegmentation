#include "stdafx.h"
#include "LandmarkLablePositionCalculatorFactory.h"
#include "LandmarkLablePositionCalculator.h"
#include "LandmarkLablePositionCalculatorSpine.h"
 

std::shared_ptr <parcast::ILandmarkLablePositionCalculator> parcast::LandmarkLablePositionCalculatorFactory::Create(const PointD3& minBounding,
	const PointD3& maxBounding, const double handleLength, const double offsetAngle, misApplicationType type)
{
	std::shared_ptr <ILandmarkLablePositionCalculator> LandmarkLablePositionCalculator;
	switch (type)
	{
	case misApplicationType::Spine:

		LandmarkLablePositionCalculator = std::make_shared<parcast::LandmarkLablePositionCalculatorSpine>(minBounding, maxBounding, handleLength, offsetAngle);
		break;
	default:
		LandmarkLablePositionCalculator =
			std::make_shared<parcast::LandmarkLablePositionCalculator>(minBounding, maxBounding, handleLength, offsetAngle);
		break;


	}
	return LandmarkLablePositionCalculator;
}
