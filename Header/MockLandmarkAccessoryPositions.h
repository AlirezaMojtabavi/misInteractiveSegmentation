#pragma once

#include <turtle/mock.hpp>

#include "ILandmarkAccessoryPositions.h"

MOCK_BASE_CLASS( MockLandmarkAccessoryPositions, ILandmarkAccessoryPositions )
{
	MOCK_NON_CONST_METHOD(SetLandmarkPosition, 1, void (const itk::Point<double, 3> &));
	MOCK_CONST_METHOD(GetLabelPosition, 0, itk::Point<double, 3> ());	
	MOCK_CONST_METHOD(GetCameraPosition, 0, itk::Point<double, 3> ());
};

