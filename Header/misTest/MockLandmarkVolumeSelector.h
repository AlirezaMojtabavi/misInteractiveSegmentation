#pragma once
#include "ILandmarkVolumeSelector.h"

MOCK_BASE_CLASS(MockLandmarkVolumeSelector, ILandmarkVolumeSelector)
{
	MOCK_CONST_METHOD(GetLandmarkTypeOfVolume, 1, misLandmarkType(misVolumeViewingTypes));

};

