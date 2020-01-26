#include "StdAfx.h"
#include "misViewerFactory.h"
#include "misEnumUtilities.h"
#include "misVolumeSlicer.h"
#include "mis3DViewer.h"
#include "misVoreenVolumeRenderingViewer.h"
#include "mis3DVolumeRenderer.h"
#include "misVolumePointPicker.h"
#include "misRepresentationFactory.h"
#include "misUpdateLandmarkCameraView.h"
#include "misApplicationSetting.h"
#include "misInitializeScrewWidget.h"
#include "misPlanSourceFactory.h"
#include "MedicalCameraDirectionFactory.h"
#include "misCursorService.h"
#include "SlicerPointSelectAction.h"
#include "BackToPanMode.h"
#include "LandmarkViewer.h"
#include "../misViewer/SlicerPointSelectActionLandamrk.h"
#include "Volume2DPointSelectAction.h"
#include "../misViewer/SlicerLandmarkViewer.h"

using namespace parcast;

std::shared_ptr<IVolumeSlicer> misViewerFactory::CreateImageViewer(std::shared_ptr<Iwindows> pWindow,
                                                                   int index,
                                                                   misSurgeryDirectionViewerType currentViewerProp,
                                                                   double VisibilityMarginInAnatomicalPlanesDirection,
                                                                   bool displayCross,
                                                                   vtkSmartPointer<misInteractorSTyleImageExtend>
                                                                   imageExtend,
                                                                   misVolumeRendererContainer::Pointer dummy,
                                                                   std::shared_ptr<ICursorService> cursorService,
                                                                   std::shared_ptr<misCameraInteraction>
                                                                   cameraInteraction)
{
	//NOTE: Surgery Type is available here,use it for your need. pCurrentViewerProp.SurgeryType

	auto viewer3d = std::make_shared<mis3DViewer>(misVolumePointPicker::New());
	auto planSourceFactory = std::make_shared<misPlanSourceFactory>();
	auto appMode = misApplicationSetting::GetInstance()->m_WorkflowButtonSet;
	auto cornerProp = std::make_shared<misCornerProperties>(appMode);
	using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;
	auto screwServiceList = std::make_shared<ScrewListType>();
	auto screwInitialize = std::make_unique<misInitializeScrewWidget>(screwServiceList,
	                                                                  pWindow->GetInterActor(), cornerProp,
	                                                                  planSourceFactory, appMode, displayCross);
	auto measurement = misMeasurment::New();
	auto backToPanMode = std::make_shared<BackToPanMode>(measurement, imageExtend, viewer3d, dummy);

	auto volumeSlicer = std::make_shared<misVolumeSlicer>(screwServiceList, pWindow, index, viewer3d, cornerProp,
	                                                      std::move(screwInitialize),
	                                                      imageExtend, measurement, dummy, cursorService, backToPanMode,
	                                                      VisibilityMarginInAnatomicalPlanesDirection,
	                                                      cameraInteraction);
	const auto pointSelectCallBack = vtkSmartPointer<SlicerPointSelectAction>::New();
	pointSelectCallBack->Create(viewer3d, volumeSlicer, cornerProp, imageExtend, backToPanMode,
	                            dummy, cursorService, volumeSlicer->GetCameraService());
	const auto pairEvent = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(
		vtkCommand::LeftButtonPressEvent, pointSelectCallBack);
	const auto pairEvent2 = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(
		vtkCommand::RightButtonPressEvent, pointSelectCallBack);
	volumeSlicer->AddPointSelectObserver(pairEvent);
	volumeSlicer->AddPointSelectObserver(pairEvent2);
	return volumeSlicer;
}


std::shared_ptr<IVolume3DRenderer> misViewerFactory::CreateVolumeViewer(std::shared_ptr<Iwindows> pWindow, int index,
                                                                        misSurgeryDirectionViewerType currentViewerProp,
                                                                        bool displayCross)
{
	//NOTE: Surgery Type is available here,use it for your need. pCurrentViewerProp.SurgeryType

	std::shared_ptr<mis3DVolumeRenderer> viewer;
	auto viewer3d = std::make_shared<mis3DViewer>(misVolumePointPicker::New());
	auto voluemRender = std::make_shared<misVoreenVolumeRenderingViewer>(nullptr);
	if (currentViewerProp.viewerType == Viewer3DLandmarkPlanning)
	{
		auto planSourceFactory = std::make_shared<misPlanSourceFactory>();
		auto appMode = misApplicationSetting::GetInstance()->m_WorkflowButtonSet;
		auto cornerProp = std::make_shared<misCornerProperties>(appMode);
		using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;
		auto screwServiceList = std::make_shared<ScrewListType>();
		auto dummy = misVolumeRendererContainer::New();
		auto screwInitilize = std::make_unique<misInitializeScrewWidget>(screwServiceList,
		                                                                 pWindow->GetInterActor(), cornerProp,
		                                                                 planSourceFactory, appMode, displayCross);
		auto medicalCameraDirection = parcast::MedicalCameraDirectionFactory::Create(viewer3d, appMode);
		viewer = std::make_shared<mis3DVolumeRenderer>(screwServiceList, pWindow, index, viewer3d, cornerProp, std::move(screwInitilize), medicalCameraDirection,
			voluemRender, dummy);
	}
	else
	{
		const auto settingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();
		auto appMode = misApplicationSetting::GetInstance()->m_WorkflowButtonSet;
		auto cornerProp = std::make_shared<misCornerProperties>(appMode);
		auto planSourceFactory = std::make_shared<misPlanSourceFactory>();
		using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;
		auto screwServiceList = std::make_shared<ScrewListType>();
		auto dummy = misVolumeRendererContainer::New();
		auto screwInitilize = std::make_unique<misInitializeScrewWidget>(screwServiceList,
		                                                                 pWindow->GetInterActor(), cornerProp,
		                                                                 planSourceFactory, appMode, displayCross);
		auto medicalCameraDirection = parcast::MedicalCameraDirectionFactory::Create(viewer3d, appMode);
		viewer = std::make_shared<mis3DVolumeRenderer>(screwServiceList, pWindow, index, viewer3d, cornerProp,
			std::move(screwInitilize), medicalCameraDirection, voluemRender, dummy);

	}

	return viewer;
}

std::shared_ptr<IRepresentationFactory> misViewerFactory::GetRepresentationFactory() const
{
	return std::make_shared<misRepresentationFactory>();
}

std::shared_ptr<parcast::ILandmarkViewer> misViewerFactory::CreateImageLandmarkViewer(
	std::shared_ptr<IVolumeSlicer> volumeRenderer,
	misViewerTypeDirection viewrType,
	std::shared_ptr<IUpdateLandmarkCameraView> updateLandmarkCameraViewer,
	std::shared_ptr<LandmarkDataAndType> landmark, double differenceForViewingSeed,
	misVolumeRendererContainer::Pointer dummy, std::shared_ptr<ICursorService> cursorService,
	std::shared_ptr<misCameraInteraction> cameraInteraction)
{
	auto pointSelectCallBack = vtkSmartPointer<SlicerPointSelectActionLandamrk>::New();
 	auto landmarkViewer= std::make_shared<parcast::SlicerLandmarkViewer>(volumeRenderer->Get3DViewer(), landmark, volumeRenderer->GetCornerProperties(), cursorService,
	                                                 updateLandmarkCameraViewer, differenceForViewingSeed, viewrType, dummy);
	pointSelectCallBack->Create(landmarkViewer, volumeRenderer->Get3DViewer(), volumeRenderer->GetCornerProperties(), dummy,
	                            cursorService, landmark);
	const auto LeftButtonPressEventCallBack = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(
		vtkCommand::LeftButtonPressEvent, pointSelectCallBack);
	const auto RightButtonPressEventCallback = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(
		vtkCommand::RightButtonPressEvent, pointSelectCallBack);
	volumeRenderer->AddPointSelectObserver(LeftButtonPressEventCallBack);
	volumeRenderer->AddPointSelectObserver(RightButtonPressEventCallback);
	return landmarkViewer;
}
