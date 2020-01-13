#pragma once
#include "IDefualtVolumeThresholdFinder.h"
#include "IImage.h"

class misDefualtVolumeThresholdFinder : public IDefualtVolumeThresholdFinder
{
public:
 	double GetVolumeThreshold(misVolumeViewingTypes volumeType, IImage* image) ;
};

