#pragma once
#include "misobjectProperitiesEnums.h"
#include "misVolumeViewingTypes.h"
#include "IImage.h"

class IDefualtVolumeThresholdFinder
{
public:
	virtual ~IDefualtVolumeThresholdFinder() = default;
	virtual double  GetVolumeThreshold(misVolumeViewingTypes volumeType, IImage* image) = 0;
};
