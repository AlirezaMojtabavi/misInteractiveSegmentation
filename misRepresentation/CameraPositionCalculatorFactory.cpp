#include "stdafx.h"
#include "CameraPositionCalculatorFactory.h"
#include "CameraPositionCalculator.h"
#include "CameraPositionCalculatorSpine.h"



using namespace parcast;

std::shared_ptr <ICameraPositionCalculator> CameraPositionCalculatorFactory::Create(PointD3 minBounding,
	PointD3 maxBounding, const double handleLength, misApplicationType type)
{
	std::shared_ptr <ICameraPositionCalculator> CameraPositionCalculator;
	switch (type)
	{
	case misApplicationType::Spine:
		CameraPositionCalculator = std::make_shared<parcast::CameraPositionCalculatorSpine>( handleLength);
		break;
	default:
		CameraPositionCalculator = std::make_shared<parcast::CameraPositionCalculator>(minBounding, maxBounding, handleLength);
		break;


	}
	return CameraPositionCalculator;
}