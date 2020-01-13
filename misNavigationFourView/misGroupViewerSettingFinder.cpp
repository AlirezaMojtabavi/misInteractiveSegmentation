#include "stdafx.h"
#include "misGroupViewerSettingFinder.h"

#include "SplitString.h"
#include "misApplicationSetting.h"
#include "misTabAndSubTabName.h"
#include "misViewElementGroup.h"
#include "misENTBraineNavigationLayoutFactory.h"
#include "misBiopsyNavigationLayout.h"
#include "misSpineNavigationLayout.h"
#include "misWidgetColorReader.h"
#include "misCMFNavigationLayout.h"

using namespace std;

std::shared_ptr<IGroupViewerSetting> misGroupViewerSettingFinder::MakePckageGroupViewer(string subTabName)
{
	std::shared_ptr<IGroupViewerSetting> viewerLayout = std::make_shared<misGroupViewerSetting>();
	misTabAndSubTabName* tabsubtabNames = misTabAndSubTabName::GetInstanse();
	if ("dataUplodingSubTab" == subTabName)
		viewerLayout = CreateDataUploading();
	if("dataCheckingSubTab" == subTabName) 
		viewerLayout = CreateDataChecking();
	else if("dataCorrelationSubTab" == subTabName) 
		viewerLayout = CreateImageCorrelation();
	else if("segmentationSubTab" == subTabName) 
	{
		viewerLayout->SetMainWidgetType(CompleteCursor);
		viewerLayout->SetLandmarkExisted(true);
		viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misSkinviewing);
		misViewElementGroup  axial(1 , AxialDirection);
		misViewElementGroup  coronal(1 , CoronalDirection);
		misViewElementGroup  sagittal(1 , SagittalDirection);
		misViewElementGroup  volume(1 , Viewer3DLandmark);
		viewerLayout->AddWindowGroup(axial);
		viewerLayout->AddWindowGroup(coronal);
		viewerLayout->AddWindowGroup(sagittal);
		viewerLayout->AddWindowGroup(volume);
	}
	else if("compositeMakingSubTab" == subTabName) 
	{
		viewerLayout->SetMainWidgetType(CompleteCursor);
		viewerLayout->SetLandmarkExisted(false);
		viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misSkinviewing);
		misViewElementGroup  axial(1 , AxialDirection);
		misViewElementGroup  coronal(1 , CoronalDirection);
		misViewElementGroup  sagittal(1 , SagittalDirection);
		misViewElementGroup  volume(1 , Viewer3DLandmark);
		viewerLayout->AddWindowGroup(axial);
		viewerLayout->AddWindowGroup(coronal);
		viewerLayout->AddWindowGroup(sagittal);
		viewerLayout->AddWindowGroup(volume);
	}
	else if("biopsyPlanningSubTab" == subTabName) 
	{
		viewerLayout->SetMainWidgetType(PreciseCursor);
		viewerLayout->SetLandmarkExisted(true);
		viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misSkinFilledViewing);
		misViewElementGroup  axial(1 , AxialDirection);
		misViewElementGroup  coronal(1 , CoronalDirection);
		misViewElementGroup  sagittal(1 , SagittalDirection);
		misViewElementGroup  volume(1 , Viewer3DLandmarkPlanning);
		viewerLayout->AddWindowGroup(axial);
		viewerLayout->AddWindowGroup(coronal);
		viewerLayout->AddWindowGroup(sagittal);
		viewerLayout->AddWindowGroup(volume);
	}	
	else if("screwPlanningSubTab" == subTabName) 
		viewerLayout = CreateScrewPlanning();
	else if ("DentalImplantPlanning" == subTabName)
		viewerLayout = CreateDentalImplantPlanning();
	else if("registrationTab" == subTabName) 
	{
		viewerLayout->SetMainWidgetType(CompleteCursor);
		viewerLayout->SetLandmarkExisted(true);
		viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misSkinviewing);
		misViewElementGroup axial(1 , AxialDirection);
		misViewElementGroup coronal(1 , CoronalDirection);
		misViewElementGroup sagittal(1 , SagittalDirection);
		misViewElementGroup volume(1, Viewer3DLandmark);
		viewerLayout->AddWindowGroup(axial);
		viewerLayout->AddWindowGroup(coronal);
		viewerLayout->AddWindowGroup(sagittal);
		viewerLayout->AddWindowGroup(volume);
	}
	else if("DentalNavigationTab" == subTabName) 
		viewerLayout = CreateDentalImplantNavigation();
	else if("SpineNavigationTab" == subTabName)
		viewerLayout = CreateSpineNavigation();
	else if ("BiopsyNavigationTab" == subTabName)
		viewerLayout = CreateBiopsyNavigation();
	else if ("CMFNavigationTab" == subTabName)
		viewerLayout = CreateCMFNavigation();
	else if ("NavigationTab" == subTabName)
		viewerLayout = CreateENTBraineNavigation();
	else if(tabsubtabNames->GetSubTabNameRoboticNavigation() == subTabName) 
	{
		std::string videoType = "";
		misApplicationSetting* AppSettingInstance = misApplicationSetting::GetInstance();
		videoType =  AppSettingInstance->m_CaptureDevices.m_VideoType;
		viewerLayout->SetMainWidgetType(PreciseCursor);
		viewerLayout->SetLandmarkExisted(true);
		viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misSinusesViewing);
		misViewElementGroup  axial(1 , AxialDirection);
		misViewElementGroup  coronal(1 , CoronalDirection);
		misViewElementGroup  sagittal(1 , SagittalDirection);
		misViewElementGroup  volume(1 , Viewer3DLandmark);
		viewerLayout->AddWindowGroup(axial);
		viewerLayout->AddWindowGroup(coronal);
		viewerLayout->AddWindowGroup(sagittal);
		viewerLayout->AddWindowGroup(volume);
		if (videoType == "SONO")
		{
			misViewElementGroup  sono(1 , Viewer2DSono);
			viewerLayout->AddWindowGroup(sono);
		}
	}
	else 	if (subTabName == "test")
		CreateTestConfig(viewerLayout);
	else if (subTabName == "testNXN")
		CreateTestXnX(viewerLayout);
	else if (subTabName == "NEWTESTSHADER")
	{
		viewerLayout->SetMainWidgetType(CompleteCursor);
		viewerLayout->SetLandmarkExisted(true);
		viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misSkinviewing);
		misViewElementGroup  Axial(1, AxialDirection);
		viewerLayout->AddWindowGroup(Axial);
		misViewElementGroup  sagittal(1, SagittalDirection);
		viewerLayout->AddWindowGroup(sagittal);
		misViewElementGroup  coronal(1, CoronalDirection); 
		viewerLayout->AddWindowGroup(coronal);
		misViewElementGroup  volume(1, Viewer3DLandmark);
		viewerLayout->AddWindowGroup(volume);
	}
	auto appSettings = misApplicationSetting::GetInstance()->GetSettingsContainer();
	viewerLayout->SetWidgetColorComposition(misWidgetColorReader::GetWidgetColorCompoFromSettings(appSettings));
	viewerLayout->SetWidgetLineWidth(appSettings->GetDouble("misVisualizationSetting/WidgetProperties/LineWidthFactor"));
	return viewerLayout;
}

std::shared_ptr<IGroupViewerSetting> misGroupViewerSettingFinder::CreateImageCorrelation( )
{
	std::shared_ptr<misGroupViewerSetting> viewerLayout = std::make_shared<misGroupViewerSetting>();

	viewerLayout->SetMainWidgetType(CompleteCursor);
	viewerLayout->SetLandmarkExisted(true);
	viewerLayout->SetKeepColor(false);
	viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misSkinviewing);
	std::map<misPlaneEnum, bool>  planes1;
	planes1[FirstImage] = true;
	planes1[SecondImage] = false;
	misViewElementGroup axial1(1 , AxialDirection, planes1);
	std::map<misPlaneEnum, bool>  planes2;
	planes2[FirstImage] = false;
	planes2[SecondImage] = true;
	misViewElementGroup axial2(1 , AxialDirection,planes2 );
	misViewElementGroup axialBoth(1 , AxialDirection);
	misViewElementGroup volume(1 , Viewer3DLandmark);
	viewerLayout->AddWindowGroup(axial1);
	viewerLayout->AddWindowGroup(axial2);
	viewerLayout->AddWindowGroup(axialBoth);
	viewerLayout->AddWindowGroup(volume);

	misPlaneContrastEvent* contrastEvent = new misPlaneContrastEvent();
	viewerLayout->SetAllMapTo(contrastEvent , false);
	viewerLayout->SetElementTo(contrastEvent, 0, 2, true);
	viewerLayout->SetElementTo(contrastEvent, 1, 2, true);
	misAddLandmarkEvent* addNextLandmarkEvent = new misAddLandmarkEvent();
	viewerLayout->SetAllMapTo(addNextLandmarkEvent,false);
	viewerLayout->SetElementTo(addNextLandmarkEvent,0,2, true);
	viewerLayout->SetElementTo(addNextLandmarkEvent,0,3, true);
	viewerLayout->SetElementTo(addNextLandmarkEvent,1,2, true);
	viewerLayout->SetElementTo(addNextLandmarkEvent,1,3, true);
	misUpdatePositionEvent* updatePositionEvent = new misUpdatePositionEvent();
	viewerLayout->SetElementTo(updatePositionEvent,0,1,false);
	viewerLayout->SetElementTo(updatePositionEvent,1,0,false);
	return viewerLayout;
}



std::shared_ptr<IGroupViewerSetting> misGroupViewerSettingFinder::CreateDataChecking(  )
{
	std::shared_ptr<misGroupViewerSetting> viewerLayout = std::make_shared<misGroupViewerSetting>();

	viewerLayout->SetMainWidgetType(CompleteCursor);
	viewerLayout->SetLandmarkExisted(false);
	viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misSkinFilledViewing);
	misViewElementGroup	axial(1 , AxialDirection);
	misViewElementGroup coronal(1 , CoronalDirection);
	misViewElementGroup sagittal(1 , SagittalDirection);
	misViewElementGroup volume(1 , Viewer3DLandmark);
	viewerLayout->AddWindowGroup(axial);
	viewerLayout->AddWindowGroup(coronal);
	viewerLayout->AddWindowGroup(sagittal);
	viewerLayout->AddWindowGroup(volume);
	misROIWidgetUpdateEvent* roiUpdate = new misROIWidgetUpdateEvent();
	viewerLayout->SetAllMapTo(roiUpdate,false);
	return viewerLayout;
}
std::shared_ptr<IGroupViewerSetting> misGroupViewerSettingFinder::CreateDataUploading()
{
	std::shared_ptr<misGroupViewerSetting> viewerLayout = std::make_shared<misGroupViewerSetting>();

	viewerLayout->SetMainWidgetType(CompleteCursor);
	viewerLayout->SetLandmarkExisted(false);
	viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misSkinFilledViewing);
	misViewElementGroup	axial(1, AxialDirection);
	misViewElementGroup coronal(1, CoronalDirection);
	misViewElementGroup sagittal(1, SagittalDirection);
	misViewElementGroup volume(1, Viewer3DLandmark);
	viewerLayout->AddWindowGroup(axial);
	viewerLayout->AddWindowGroup(coronal);
	viewerLayout->AddWindowGroup(sagittal);
	viewerLayout->AddWindowGroup(volume);
	misROIWidgetUpdateEvent* roiUpdate = new misROIWidgetUpdateEvent();
	viewerLayout->SetAllMapTo(roiUpdate, false);
	return viewerLayout;
}


void misGroupViewerSettingFinder::CreateTestXnX(std::shared_ptr<IGroupViewerSetting> viewerLayout)
{
	misApplicationSetting* AppSettingInstance = misApplicationSetting::GetInstance();
	std::string videoType =  AppSettingInstance->m_CaptureDevices.m_VideoType;
	viewerLayout->SetMainWidgetType(PreciseCursor);
	viewerLayout->SetLandmarkExisted(true);
	misViewElementGroup  coronalNXN(2, CoronalDirection,
		misViewElementGroup::CreateDefaultPlaneVisibilyMap(), 5);
	viewerLayout->AddWindowGroup(coronalNXN);
}

void misGroupViewerSettingFinder::CreateTestConfig(std::shared_ptr<IGroupViewerSetting> viewerLayout )
{
	misApplicationSetting* AppSettingInstance = misApplicationSetting::GetInstance();
	std::string videoType =  AppSettingInstance->m_CaptureDevices.m_VideoType;
	misApplicationType appType =  AppSettingInstance->m_WorkflowButtonSet;
	viewerLayout->SetMainWidgetType(PreciseCursor);
	viewerLayout->SetLandmarkExisted(true);
	viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misSinusesViewing);
	misViewElementGroup  axial(1, AxialDirection);
	misViewElementGroup  coronal(1, CoronalDirection);
	misViewElementGroup  coronalNXN(2, CoronalDirection,
		misViewElementGroup::CreateDefaultPlaneVisibilyMap(), 5);
	misViewElementGroup  sagittal(1, SagittalDirection);
	misViewElementGroup  volume(1, Viewer3DLandmark);
	viewerLayout->AddWindowGroup(axial);
	viewerLayout->AddWindowGroup(coronalNXN);
	viewerLayout->AddWindowGroup(sagittal);
	viewerLayout->AddWindowGroup(volume);
}

std::shared_ptr<IGroupViewerSetting> misGroupViewerSettingFinder::CreateBiopsyNavigation()
{
	misBiopsyNavigationLayout layout;
	return layout.GetLayout();
}

std::shared_ptr<IGroupViewerSetting> misGroupViewerSettingFinder::CreateDentalImplantPlanning(  )
{
	std::shared_ptr<misGroupViewerSetting> SettingStrct = std::make_shared<misGroupViewerSetting>();

	SettingStrct->SetMainWidgetType(PreciseCursor);
	SettingStrct->SetLandmarkExisted(true);
	SettingStrct->SetVolumeViewingType(misVolumeViewingTypes::misTeethViewing);
	misViewElementGroup  axial(1 , AxialDirection);
	misViewElementGroup  coronal(1 , CoronalDirection);
	misViewElementGroup  sagittal(1 , SagittalDirection);
	misViewElementGroup  volume(1 , Viewer3DLandmark);
	misViewElementGroup  panoramic(1 , PanormaicView);
	SettingStrct->AddWindowGroup(axial);
	SettingStrct->AddWindowGroup(coronal);
	SettingStrct->AddWindowGroup(sagittal);
	SettingStrct->AddWindowGroup(volume);
	SettingStrct->AddWindowGroup(panoramic);
	return SettingStrct;
}

std::shared_ptr<IGroupViewerSetting> misGroupViewerSettingFinder::CreateScrewPlanning()
{
	std::shared_ptr<misGroupViewerSetting> SettingStrct = std::make_shared<misGroupViewerSetting>();

	SettingStrct->SetMainWidgetType(PreciseCursor);
	SettingStrct->SetLandmarkExisted(true);
	SettingStrct->SetVolumeViewingType(misVolumeViewingTypes::misBoneViwing);
	misViewElementGroup  axial(1 , AxialDirection);
	misViewElementGroup  coronal(1 , CoronalDirection);
	misViewElementGroup  sagittal(1 , SagittalDirection);
	misViewElementGroup  volume(1, Viewer3DLandmarkPlanning);
	SettingStrct->AddWindowGroup(axial);
	SettingStrct->AddWindowGroup(coronal);
	SettingStrct->AddWindowGroup(sagittal);
	SettingStrct->AddWindowGroup(volume);
	return SettingStrct;
}

std::shared_ptr<IGroupViewerSetting> misGroupViewerSettingFinder::CreateDentalImplantNavigation()
{
	std::shared_ptr<misGroupViewerSetting> viewerLayout = std::make_shared<misGroupViewerSetting>();

	viewerLayout->SetMainWidgetType(PreciseCursor);
	viewerLayout->SetLandmarkExisted(true);
	viewerLayout->SetVolumeViewingType(misVolumeViewingTypes::misTeethViewing);
	misViewElementGroup axialNxN(1, AxialDirection);
	misViewElementGroup sagittal(1, SagittalDirection);
	misViewElementGroup coronal(1, CoronalDirection);
	misViewElementGroup volume(1, Viewer3DLandmark);
	viewerLayout->AddWindowGroup(axialNxN);
	viewerLayout->AddWindowGroup(coronal);
	viewerLayout->AddWindowGroup(sagittal);
	viewerLayout->AddWindowGroup(volume);
	misViewElementGroup panoramic(1, PanormaicView);
	viewerLayout->AddWindowGroup(panoramic);
	return viewerLayout;
}

std::shared_ptr<IGroupViewerSetting> misGroupViewerSettingFinder::CreateSpineNavigation()
{
	misSpineNavigationLayout layout;
	return layout.GetLayout();
}

std::shared_ptr<IGroupViewerSetting> misGroupViewerSettingFinder::CreateENTBraineNavigation()
{
	misENTBraineNavigationLayoutFactory layout;
	return layout.GetLayout();
}

std::shared_ptr<IGroupViewerSetting> misGroupViewerSettingFinder::CreateCMFNavigation() const
{
	misCMFNavigationLayout layout;
	return layout.GetLayout();
}
