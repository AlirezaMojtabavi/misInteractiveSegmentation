#pragma once
#include "misObjectRangeStr.h"
#include "IImage.h"
#include "misVolumeViewingTypes.h"

class IValidateVolumeThreshold
{
public:
	virtual ~IValidateVolumeThreshold() = default;
	virtual boost::optional<misObjectRangeStr> GetValidObjectThresholdRange(mis3DModelTypes modeType,const IImage* image) const = 0;
	virtual double ValidateVolumeThreshold(const IImage* image, misVolumeViewingTypes volumeType, mis3DModelTypes modeType, double threshold) const = 0;

};
