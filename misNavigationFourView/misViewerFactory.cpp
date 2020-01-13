#include "StdAfx.h"
#include "misViewerFactory.h"
#include "misEnumUtilities.h"
#include "misVolumeSlicer.h"
#include "misVoreenRepresentation.h"
#include "mis3DViewer.h"
#include "misVoreenVolumeRenderingViewer.h"
#include "mis3DVolumeRenderer.h"
#include "misVolumePointPicker.h"
#include "misRepresentationFactory.h"
#include "misImageSlicerMapper.h"
#include "misUpdateLandmarkCameraView.h"
#include "misApplicationSetting.h"
#include "misUpdateplanningLandmarkView.h"
#include "misInitializeScrewWidget.h"
#include "misPlanSourceFactory.h"
#include "MedicalCameraDirectionFactory.h"
#include "IMedicalCameraDirection.h"
#include "MedicalCameraDirectionFactory.h"
#include "IMedicalCameraDirection.h"
#include "MedicalCameraDirectionFactory.h"
#include "misCursorService.h"
#include "PointSelectAction.h"
#include "BackToPanMode.h"

using namespace parcast;

std::shared_ptr<misVolumeSlicer> misViewerFactory::CreateImageViewer(std::shared_ptr<Iwindows> pWindow,
                                                                     int index,
                                                                     misSurgeryDirectionViewerType currentViewerProp,
                                                                     double VisibilityMarginInAnatomicalPlanesDirection,
                                                                     bool displayCross)
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
	auto dummy = misVolumeRendererContainer::New();
	auto imageExtend = vtkSmartPointer<misInteractorSTyleImageExtend>::New();
	auto backToPanMode = std::make_shared<BackToPanMode>(measurement, imageExtend, viewer3d, dummy);
	auto cursorService = std::make_shared<misCursorService>();
	auto landmark = std::make_shared<LandmarkDataAndType>();
	auto volumeSlicer = std::make_shared<misVolumeSlicer>(screwServiceList, pWindow, index, viewer3d, cornerProp,
	                                                      nullptr,
	                                                      std::move(screwInitialize),
	                                                      imageExtend, measurement, dummy, cursorService, backToPanMode,
	                                                      VisibilityMarginInAnatomicalPlanesDirection, landmark);
	const auto pointSelectCallBack = new PointSelectAction(viewer3d, volumeSlicer, cornerProp, imageExtend, backToPanMode,
	                                                 dummy, cursorService, volumeSlicer->GetCameraService(), landmark);
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
		auto screwInitilize = std::make_unique<misInitializeScrewWidget>(screwServiceList,
		                                                                 pWindow->GetInterActor(), cornerProp,
		                                                                 planSourceFactory, appMode, displayCross);
		auto medicalCameraDirection = parcast::MedicalCameraDirectionFactory::Create(viewer3d, appMode);
		viewer = std::make_shared<mis3DVolumeRenderer>(screwServiceList, pWindow, index, viewer3d, cornerProp, nullptr,
		                                               std::move(screwInitilize), medicalCameraDirection, voluemRender);
	}
	else
	{
		const auto settingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();
		const auto cameraDistance = settingContainer->GetDouble("RegisterationSetting/LandmarkLableCameraDistance");
		std::shared_ptr<IUpdateLandmarkCameraView> updateLandmarkCameraViewer = std::make_shared<
			misUpdateLandmarkCameraView
		>(viewer3d, cameraDistance);
		auto appMode = misApplicationSetting::GetInstance()->m_WorkflowButtonSet;
		auto cornerProp = std::make_shared<misCornerProperties>(appMode);
		auto planSourceFactory = std::make_shared<misPlanSourceFactory>();
		using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;
		auto screwServiceList = std::make_shared<ScrewListType>();

		auto screwInitilize = std::make_unique<misInitializeScrewWidget>(screwServiceList,
		                                                                 pWindow->GetInterActor(), cornerProp,
		                                                                 planSourceFactory, appMode, displayCross);
		auto medicalCameraDirection = parcast::MedicalCameraDirectionFactory::Create(viewer3d, appMode);
		viewer = std::make_shared<mis3DVolumeRenderer>(screwServiceList, pWindow, index, viewer3d, cornerProp,
		                                               updateLandmarkCameraViewer,
		                                               std::move(screwInitilize), medicalCameraDirection, voluemRender);
	}
	return viewer;
}

std::shared_ptr<IRepresentationFactory> misViewerFactory::GetRepresentationFactory() const
{
	return std::make_shared<misRepresentationFactory>();
}
