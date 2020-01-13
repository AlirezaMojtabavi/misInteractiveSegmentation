#pragma once
#include "IValidateVolumeThreshold.h"
MOCK_BASE_CLASS(MockValidateVolumeThreshold, IValidateVolumeThreshold)
{
	MOCK_CONST_METHOD(GetValidObjectThresholdRange, 2, boost::optional<misObjectRangeStr> (mis3DModelTypes, const IImage*) );
	MOCK_CONST_METHOD(ValidateVolumeThreshold, 4, double(const IImage*, misVolumeViewingTypes, mis3DModelTypes, double));

 };
