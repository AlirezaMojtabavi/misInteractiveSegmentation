#pragma once
#include "ILandmarkVolumeSelector.h"

class misLandmarkVolumeSelector : public ILandmarkVolumeSelector
{
public:
	misLandmarkType GetLandmarkTypeOfVolume(misVolumeViewingTypes) const override;
};

