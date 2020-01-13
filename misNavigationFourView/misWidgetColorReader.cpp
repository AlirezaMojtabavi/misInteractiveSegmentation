#include "stdafx.h"
#include "..\Header\misWidgetColorReader.h"
#include <SplitString.h>
#include <misApplicationSetting.h>


parcast::Color misWidgetColorReader::GetColorFromSettings(
	const std::shared_ptr<const ISettingsContainer>& settings, const std::string & settingName)
{
	const auto appSettings = misApplicationSetting::GetInstance()->GetSettingsContainer();
	parcast::SplitString<unsigned short> split;
	const auto rgbUChar = split.GetNumbers(appSettings->GetString(settingName), ' ');
	const auto red = rgbUChar[0], green = rgbUChar[1], blue = rgbUChar[2];
	return parcast::Color::FromRgb(red, green, blue);
}

parcast::AxesColors misWidgetColorReader::GetWidgetColorCompoFromSettings(
	const std::shared_ptr<const ISettingsContainer>& settings)
{
	return parcast::AxesColors{
		GetColorFromSettings(settings, "misVisualizationSetting/WidgetProperties/ColorComposition/XAxis"),
		GetColorFromSettings(settings, "misVisualizationSetting/WidgetProperties/ColorComposition/YAxis"),
		GetColorFromSettings(settings, "misVisualizationSetting/WidgetProperties/ColorComposition/ZAxis")
	};
}