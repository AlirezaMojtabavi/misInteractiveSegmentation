#include "stdafx.h"
#include "misENTBraineNavigationLayoutFactory.h"
#include "misGroupViewerSetting.h"
#include <misApplicationSetting.h>
#include <SplitString.h>
#include "misWidgetColorReader.h"

std::shared_ptr<IGroupViewerSetting> misENTBraineNavigationLayoutFactory::GetLayout() const
{
	auto viewerLayout = std::make_shared<misGroupViewerSetting>();
	viewerLayout->SetMainWidgetType(PreciseCursor);
	viewerLayout->SetLandmarkExisted(true);
	viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misSinusesViewing);
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

 

 std::shared_ptr<IGroupViewerSetting> misENTBraineNavigationLayoutFactory::GetLayoutFromFile(const std::string& layoutType) const
{
	 std::string directory = FileSystem::currentDirectory();
	 auto subDirectory = std::string("ENT");
	 auto address = "\\Resources\\Layouts\\Navigation\\" + subDirectory + "\\" + layoutType + ".xml";
	 auto file = directory + address;

	std::ifstream f;
	f.open(file, std::ios::in);
	XmlDeserializer d;
	d.read(f);
	std::shared_ptr<misGroupViewerSetting> viewerLayout = std::make_shared<misGroupViewerSetting>();
	d.deserialize("misGroupViewerSetting", *viewerLayout.get());
	viewerLayout->SetMainWidgetType(PreciseCursor);
	viewerLayout->SetLandmarkExisted(true);
	viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misSinusesViewing);
	auto appSettings = misApplicationSetting::GetInstance()->GetSettingsContainer();
	viewerLayout->SetWidgetColorComposition(misWidgetColorReader::GetWidgetColorCompoFromSettings(appSettings));
	viewerLayout->SetWidgetLineWidth(appSettings->GetDouble("misVisualizationSetting/WidgetProperties/LineWidthFactor"));

	return viewerLayout;
}
 