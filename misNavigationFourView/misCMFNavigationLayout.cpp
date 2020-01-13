#include "stdafx.h"
#include "misCMFNavigationLayout.h"
#include "misGroupViewerSetting.h"
#include "misWidgetColorReader.h"
#include <misApplicationSetting.h>

std::shared_ptr<IGroupViewerSetting> misCMFNavigationLayout::GetLayout() const
{
	auto viewerLayout = std::make_shared<misGroupViewerSetting>();
	viewerLayout->SetMainWidgetType(PreciseCursor);
	viewerLayout->SetLandmarkExisted(true);
	viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misBoneViwing);
	misViewElementGroup axial(1, AxialDirection);
	misViewElementGroup sagittal(1, SagittalDirection);
	misViewElementGroup volume(1, Viewer3DLandmark);
	misViewElementGroup coronal(1, CoronalDirection);
	viewerLayout->AddWindowGroup(axial);
	viewerLayout->AddWindowGroup(coronal);
	viewerLayout->AddWindowGroup(sagittal);
	viewerLayout->AddWindowGroup(volume);
	auto appSettings = misApplicationSetting::GetInstance()->GetSettingsContainer();
	viewerLayout->SetWidgetColorComposition(misWidgetColorReader::GetWidgetColorCompoFromSettings(appSettings));
	viewerLayout->SetWidgetLineWidth(appSettings->GetDouble("misVisualizationSetting/WidgetProperties/LineWidthFactor"));

	return viewerLayout;
}

std::shared_ptr<IGroupViewerSetting> misCMFNavigationLayout::GetLayoutFromFile(const std::string& layoutName)const
{
	std::string directory = FileSystem::currentDirectory();
	auto subDirectory = std::string("CMF");
	auto address = "\\Resources\\Layouts\\Navigation\\" + subDirectory + "\\" + layoutName + ".xml";
	auto file = directory + address;

	std::ifstream f;
	f.open(file, std::ios::in);
	XmlDeserializer d;
	d.read(f);
	auto viewerLayout = std::make_shared<misGroupViewerSetting>();
	d.deserialize("misGroupViewerSetting", *viewerLayout.get());
	auto appSettings = misApplicationSetting::GetInstance()->GetSettingsContainer();
	viewerLayout->SetWidgetColorComposition(misWidgetColorReader::GetWidgetColorCompoFromSettings(appSettings));
	viewerLayout->SetWidgetLineWidth(appSettings->GetDouble("misVisualizationSetting/WidgetProperties/LineWidthFactor"));

	return viewerLayout;
}
