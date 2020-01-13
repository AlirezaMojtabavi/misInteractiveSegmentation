#pragma once
#include "misApplication.h"
#include "IImage.h"

struct misSliderStrc;

namespace parcast
{

	class IVolumeThresholdSliderRangeUpdater
	{
	public:
		virtual void Update(std::weak_ptr<IImage> image, const misVisualizationSetting& visulizationSetting) const = 0;
		virtual void SetImageModality(const misImageDataModality& modality) = 0;
	};

}