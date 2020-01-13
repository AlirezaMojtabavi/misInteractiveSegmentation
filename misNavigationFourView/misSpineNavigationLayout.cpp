#include "stdafx.h"
#include "misSpineNavigationLayout.h"
#include "misGroupViewerSetting.h"
#include "misWidgetColorReader.h"
#include <misApplicationSetting.h>


misSpineNavigationLayout::misSpineNavigationLayout()
{
}


misSpineNavigationLayout::~misSpineNavigationLayout()
{
}

std::shared_ptr<IGroupViewerSetting> misSpineNavigationLayout::GetLayout() const
{
	std::shared_ptr<misGroupViewerSetting> SettingStrct = std::make_shared<misGroupViewerSetting>();

	SettingStrct->SetMainWidgetType(PreciseCursor);
	SettingStrct->SetLandmarkExisted(true);
	SettingStrct->SetVolumeViewingType(misVolumeViewingTypes::misSpineViewing);
	misViewElementGroup axial(1, AxialDirection);
	axial.SetShowToolExtension(false);
	misViewElementGroup coronalNxN(1, CoronalDirection);
	coronalNxN.SetShowToolExtension(false);
	misViewElementGroup sagittal(1, SagittalDirection);
	sagittal.SetShowToolExtension(false);
	misViewElementGroup volume(1, Viewer3DLandmark);
	volume.SetShowToolExtension(false);
	SettingStrct->AddWindowGroup(axial);
	SettingStrct->AddWindowGroup(coronalNxN);
	SettingStrct->AddWindowGroup(sagittal);
	SettingStrct->AddWindowGroup(volume);
	auto appSettings = misApplicationSetting::GetInstance()->GetSettingsContainer();
	SettingStrct->SetWidgetColorComposition(misWidgetColorReader::GetWidgetColorCompoFromSettings(appSettings));
	SettingStrct->SetWidgetLineWidth(appSettings->GetDouble("misVisualizationSetting/WidgetProperties/LineWidthFactor"));

	return SettingStrct;
}

std::shared_ptr<IGroupViewerSetting> misSpineNavigationLayout::GetLayoutFromFile(const std::string& layoutType) const
{
	const std::string directory = FileSystem::currentDirectory();
	const auto subDirectory = std::string("Spine");
	const auto address = R"(\Resources\Layouts\Navigation\)" + subDirectory + "\\" + layoutType + ".xml";
	const auto file = directory + address;
	std::ifstream f;
	f.open(file, std::ios::in);
	XmlDeserializer d;
	d.read(f);
	auto viewerLayout = std::make_shared<misGroupViewerSetting>();
	d.deserialize("misGroupViewerSetting", *viewerLayout.get());
	const auto appSettings = misApplicationSetting::GetInstance()->GetSettingsContainer();
	viewerLayout->SetWidgetColorComposition(misWidgetColorReader::GetWidgetColorCompoFromSettings(appSettings));
	viewerLayout->SetWidgetLineWidth(appSettings->GetDouble("misVisualizationSetting/WidgetProperties/LineWidthFactor"));

	return viewerLayout;
}
