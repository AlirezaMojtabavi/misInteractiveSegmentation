#pragma once
#include <AxesColors.h>
#include <ISettingsContainer.h>

class misWidgetColorReader
{
public:
	static parcast::Color GetColorFromSettings(
		const std::shared_ptr<const ISettingsContainer>& settings, const std::string& settingName);
	static parcast::AxesColors GetWidgetColorCompoFromSettings(const std::shared_ptr<const ISettingsContainer>& settings);
};

