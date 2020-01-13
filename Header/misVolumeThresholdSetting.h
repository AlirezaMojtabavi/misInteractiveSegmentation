#pragma once
#include "IImage.h"

enum mis3DModelTypes;

class misVolumeThresholdSetting
{
public:
	misVolumeThresholdSetting(std::shared_ptr<IImage> image);
	double GetObjectThresholdBasedNormalizedThreshold(const mis3DModelTypes obJcetType, double threshold);
	double GetNormalizedObjectThresholdBasedOnThreshold(const mis3DModelTypes obJcetType, double threshold);
	double GetDefaultVolumeThreshold(const mis3DModelTypes obJcetType);

 private:
	std::shared_ptr<IImage> m_Image;
};

