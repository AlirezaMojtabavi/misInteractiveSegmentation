#pragma once
#include "IDefualtVolumeThresholdFinder.h"
MOCK_BASE_CLASS(MockDefualtVolumeThresholdFinder, IDefualtVolumeThresholdFinder)
{
			MOCK_NON_CONST_METHOD(GetVolumeThreshold, 2, double  (misVolumeViewingTypes, IImage*) );
};