#pragma once

#include "IVolumeThresholdSliderRangeUpdater.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockDataCheckingThresholdSliderRangeUpdater, IVolumeThresholdSliderRangeUpdater)
	{
		MOCK_CONST_METHOD(Update, 0, void());
		MOCK_NON_CONST_METHOD(SetImageModality, 1, void(const misImageDataModality& modality));
	};
}