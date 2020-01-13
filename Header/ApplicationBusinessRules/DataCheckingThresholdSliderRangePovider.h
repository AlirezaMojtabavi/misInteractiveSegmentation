#pragma once

#include "IDataCheckingThresholdSliderRangePovider.h"

class ISettingsContainer;

namespace parcast
{

	class DataCheckingThresholdSliderRangePovider : public IDataCheckingThresholdSliderRangePovider
	{
	public:
		DataCheckingThresholdSliderRangePovider(std::shared_ptr<ISettingsContainer> appSettingContainer);
		misSliderStrc GetSliderRange() const override;
		void SetImageModality(const misImageDataModality& modality) override;

	private:
		std::shared_ptr<ISettingsContainer> m_AppSettingContainer;
		misImageDataModality m_Modality;
	};

}
