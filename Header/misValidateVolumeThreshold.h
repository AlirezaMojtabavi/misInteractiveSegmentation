#pragma once
#include "IValidateVolumeThreshold.h"
#include "IImage.h"

class misValidateVolumeThreshold : public IValidateVolumeThreshold
{
public:
	misValidateVolumeThreshold(ObjectRangeListTypdef defaultRangeList);
	boost::optional<misObjectRangeStr> GetValidObjectThresholdRange(mis3DModelTypes modeType, const IImage* image) const override;
	double ValidateVolumeThreshold(const IImage* image, misVolumeViewingTypes volumeType, mis3DModelTypes modeType, double threshold) const override;

private:

	ObjectRangeListTypdef m_DefaultRangeList;

};
