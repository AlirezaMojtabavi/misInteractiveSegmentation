#pragma once
#include "misDataSetsUtility.h"
#include "misLandmarkenums.h"

class ILandmarkVolumeSelector
{
public :
	virtual ~ILandmarkVolumeSelector() = default;
	virtual misLandmarkType GetLandmarkTypeOfVolume(misVolumeViewingTypes) const = 0;
};
