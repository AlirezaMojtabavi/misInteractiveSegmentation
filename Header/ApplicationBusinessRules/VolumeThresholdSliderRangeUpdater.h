#pragma once

#include "IVolumeThresholdSliderRangeUpdater.h"
#include "IVolumeThresholdUiUpdater.h"

class ISettingsContainer;

namespace parcast
{

	class VolumeThresholdSliderRangeUpdater : public IVolumeThresholdSliderRangeUpdater
	{
	public:
		VolumeThresholdSliderRangeUpdater(
			std::shared_ptr<ISettingsContainer> appSettingContainer,
			std::shared_ptr<IVolumeThresholdUiUpdater> uiUpdater);
		void Update(std::weak_ptr<IImage> image, const misVisualizationSetting& visulizationSetting) const override;
		void SetImageModality(const misImageDataModality& modality) override;

	private:
		std::shared_ptr<ISettingsContainer> m_AppSettingContainer;
		std::shared_ptr<IVolumeThresholdUiUpdater> m_UiUpdater;
		misImageDataModality m_Modality;
	};

}
