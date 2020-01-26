#include "stdafx.h"
#include "misGroupViewerFactory.h"
#include "ISubsequenceLayout.h"
#include "IGroupViewerSetting.h"
#include "misSurgeryDirectionViewerType.h"
#include "misVolumeSlicer.h"
#include "misPackage3DDataRenderingAdapter.h"
#include "misGroupViewer.h"
#include "misWindow.h"
#include "misPackage2DDataRenderingAdapter.h"
#include "IViewerFactory.h"
#include "ICursorService.h"
#include "mis2DImageRenderingAdapter.h"
#include "misImageToTextureMap.h"
#include "mis2DPackageTransformUpdater.h"
#include "mis3DPackageTransformUpdater.h"
#include "mis3DImageRenderer.h"
#include "VolumeViewerInitilizer.h"
#include "misLandmarkViewerCollection.h"
#include "LandmarkViewer.h"
#include "misPackage2DLandamrkAdapter.h"
#include "misUpdateLandmarkCameraView.h"
#include "misCursorService.h"
#include "Volume2DPointSelectAction.h"
#include "../misViewer/Volume3DLandmarkViewer.h"
#include "misPackage3DLandmarkAdapter.h"
#include "../misViewer/SlicerPointSelectActionLandamrk.h"
#include "../misViewer/Volume3DSelectActionLandamrk.h"


misGroupViewerFactory::misGroupViewerFactory(std::shared_ptr<Injector> injector)
{
	if (!injector)
		m_Injector = std::make_shared<Injector>();
}


std::shared_ptr<INavigationViewersNView> misGroupViewerFactory::Create(std::shared_ptr<IGroupViewerSetting> setting,
                                                                       std::shared_ptr<ISubsequenceLayout> model,
                                                                       misApplicationType applicationType,
                                                                       std::shared_ptr<IViewerFactory> viewerFactory, 
	std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationMananger, double visibiltyLandmarkOffset)
{
	auto groupViewer = std::make_shared<misGroupViewer>(correlationMananger, setting);
	auto layOut = setting->GetWindowsLayout();
	std::vector<std::map<misPlaneEnum, bool>> defaultVisibilityPlanes;

	for (unsigned int i = 0; i < setting->GetNumberOfGroupElement(); i++)
	{
		misWindowModel newWindow;
		if (!model->GetWindow(i, newWindow))
			continue;
		std::shared_ptr<Iwindows> windowRender = m_Injector->CreateRenderingWindow(newWindow);

		misViewElementGroup viewers = setting->GetElement(i);
		auto  typeOfViewer = viewers.GetTypeOfViewer();
		if (typeOfViewer == Video)
			continue;
		int numofViewerInGroup = viewers.GetNumberOfViewer();

		for (int j = 0; j < numofViewerInGroup; j++)
		{
			misViewingWindowElement viewerElement = viewers.GetViewer(j);
			int rendererIndex = 0;
			if (setting->GetOrientation(i) == UNKnownDirection)
				rendererIndex = windowRender->GenerateRenderWindow(Iwindows::VolumeViewer, viewerElement.GetViewPort());
			else
			{
				rendererIndex = windowRender->GenerateRenderWindow(Iwindows::NoViewer, viewerElement.GetViewPort());
			}

			misSurgeryDirectionViewerType viewerProp;
			viewerProp.surgeryType = setting->GetSurgeryType();
			viewerProp.viewerType = setting->GetTypeOfViewer(i);
			viewerProp.orientation = setting->GetOrientation(i);
			std::shared_ptr<IPackageDataRenderingAdapter> newPackageViewer;
			if (viewerProp.viewerType == Viewer3DLandmark || viewerProp.viewerType == Viewer3DLandmarkPlanning)
			{
				auto isCrossSectionVisible = !(model->GetName() == "BiopsyNavigationTab" && applicationType == misApplicationType::Biopsy);
				auto viewer = viewerFactory->CreateVolumeViewer(windowRender, rendererIndex, viewerProp, isCrossSectionVisible);
				auto volumeViewerInitializer = std::make_shared<VolumeViewerInitilizer>(viewer, viewerFactory->GetRepresentationFactory(),viewerProp);
				auto ImageRenderer = std::make_shared<mis3DImageRenderer>(viewer, viewerProp, viewerFactory,volumeViewerInitializer);

				auto transformUpdater3D = std::make_shared<mis3DPackageTransformUpdater>(correlationMananger,
					viewer);
				newPackageViewer = std::make_shared<misPackage3DDataRenderingAdapter>(correlationMananger, 
					windowRender, rendererIndex, viewerProp, viewer, ImageRenderer, transformUpdater3D,volumeViewerInitializer);
				groupViewer->Add3DViewer(std::dynamic_pointer_cast<misPackage3DDataRenderingAdapter>(newPackageViewer),
				                         windowRender);
			}

			else
			{
				auto imageExtend = vtkSmartPointer<misInteractorSTyleImageExtend>::New();
				auto dummy = misVolumeRendererContainer::New();
				auto cameraInteraction = std::make_shared<misCameraInteraction>();
				auto cursorService = std::make_shared<misCursorService>();
				auto isCrossSectionVisible = !(model->GetName() == "BiopsyNavigationTab" && applicationType == misApplicationType::Biopsy);
				auto viewer = viewerFactory->CreateImageViewer(windowRender, rendererIndex, viewerProp, visibiltyLandmarkOffset,
					isCrossSectionVisible, 
					imageExtend, dummy, cursorService,  cameraInteraction);
				auto imageRenderer = std::make_unique<mis2DImageRenderingAdapter>(viewer, viewerProp,
				                                                                  viewerFactory->GetRepresentationFactory(),
				                                                                  misImageToTextureMap::GetInstance());
				auto transformUpdater2D = std::make_shared<mis2DPackageTransformUpdater>(correlationMananger,
					viewer);
				newPackageViewer = std::make_shared<misPackage2DDataRenderingAdapter>(correlationMananger, viewerProp,
				                                                                      viewerElement.GetOffset(), viewer,                                                                    				                                                                      viewerFactory->GetRepresentationFactory(),
				                                                                      std::move(imageRenderer), 
					transformUpdater2D);

				groupViewer->Add2DViewer(std::dynamic_pointer_cast<misPackage2DDataRenderingAdapter>(newPackageViewer),
				                         windowRender);
			}
			auto viewer = newPackageViewer->GetViewer();
			newPackageViewer->SetVolumeViewingType(setting->GetVolumeViewingType());
			viewer->GetCursorService()->SetAxesColors(setting->GetWidgetColorComposition());
			viewer->GetCursorService()->SetWidgetLineWeight(setting->GetWidgetLineWidth());
			viewer->SetViewPort(viewerElement.GetViewPort());
			viewer->SetTypeDirection(typeOfViewer);
			if (numofViewerInGroup > 1)
				viewer->SetShowManModel(false);
			auto imageViewer = std::dynamic_pointer_cast<misVolumeSlicer>(viewer);
			if (imageViewer)

			{
				imageViewer->SetSurgeryType(applicationType);
				imageViewer->SetObliqueFlag(layOut.GetWindows()[i].IsOblique());
			}
			defaultVisibilityPlanes.push_back(setting->GetPlaneVisibilityStatus(i));
		}
	}

	groupViewer->SetDefaultVisibilityMap(defaultVisibilityPlanes);

	return groupViewer;
}

std::shared_ptr<ILandmarkViewerCollection> misGroupViewerFactory::CreateLandmarkViewerCollection(
	std::shared_ptr<IGroupViewerSetting> setting, std::shared_ptr<ISubsequenceLayout> model,
	std::vector<std::shared_ptr<IVolumeRenderer>> viewers,
	misApplicationType applicationType, std::shared_ptr<IViewerFactory> factory,
	 double visibiltyLandmarkOffset)
{
	const auto settingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();
	auto landmarkViewerCollection = std::make_shared<misLandmarkViewerCollection>(setting);
	auto layOut = setting->GetWindowsLayout();
	std::vector<std::map<misPlaneEnum, bool>> defaultVisibilityPlanes;
	for (auto viewer : viewers)
		{
			const auto typeDirection = viewer->GetTypeDirection();
		if (typeDirection == misViewerTypeDirection::AxialDirection || typeDirection == misViewerTypeDirection::CoronalDirection
			|| typeDirection == misViewerTypeDirection::SagittalDirection)
		{
			auto pointLeftButtonCallback = vtkSmartPointer<Volume2DPointSelectAction>::New();
			auto landmarkData = std::make_shared<LandmarkDataAndType>();
			const auto cameraDistance = settingContainer->GetDouble("RegisterationSetting/LandmarkLableCameraDistance");
			auto cameraLandamrkView = std::make_shared<
				misUpdateLandmarkCameraView
			>(viewer->Get3DViewer(), cameraDistance);
			auto landmarkViewer = factory->CreateImageLandmarkViewer(std::dynamic_pointer_cast<IVolumeSlicer>(viewer),typeDirection,
				cameraLandamrkView, landmarkData, visibiltyLandmarkOffset, viewer->GetDummySubject(),	viewer->GetCursorService(),
				(std::dynamic_pointer_cast<IVolumeSlicer>(viewer)->GetCameraService() ));
			pointLeftButtonCallback->Create(landmarkData, landmarkViewer, viewer->GetDummySubject());
			viewer->GetCursorService()->AddObserver(pointLeftButtonCallback);

			auto landmarkAdapter = std::make_shared<misPackage2DLandmarkAdapter>(landmarkViewer);
			landmarkViewerCollection->AddAdapter(landmarkAdapter);
		}
		else
		{
	
			auto pointLeftButtonCallback = vtkSmartPointer<Volume3DSelectActionLandamrk>::New();
			auto landmarkData = std::make_shared<LandmarkDataAndType>();
			const auto cameraDistance = settingContainer->GetDouble("RegisterationSetting/LandmarkLableCameraDistance");
			auto cameraLandamrkView = std::make_shared<
				misUpdateLandmarkCameraView
			>(viewer->Get3DViewer(), cameraDistance);
			auto landmarkViewer = std::make_shared<parcast::Volume3DLandmarkViewer>(
				viewer->Get3DViewer(), landmarkData, viewer->GetCornerProperties(), viewer->GetCursorService(),
				cameraLandamrkView, visibiltyLandmarkOffset, viewer->GetDummySubject());
				pointLeftButtonCallback->Create(landmarkViewer, viewer->Get3DViewer(), viewer->GetCursorService(), viewer->GetCornerProperties(),
				viewer->GetDummySubject(), landmarkData);
			const auto LeftButtonPressEventCallBack = std::make_pair<unsigned long, vtkSmartPointer<vtkCommand>>(
				vtkCommand::LeftButtonPressEvent, pointLeftButtonCallback);
			viewer->AddPointSelectObserver(LeftButtonPressEventCallBack);
			auto landmarkAdapter = std::make_shared<misPackage3DLandmarkAdapter>(landmarkViewer);
			landmarkViewerCollection->AddAdapter(landmarkAdapter);
		}
		}
	return landmarkViewerCollection;

}


std::shared_ptr<Iwindows> misGroupViewerFactory::Injector::CreateRenderingWindow(const misWindowModel& model)
{
	auto window =  std::make_shared<misWindow>();
	window->GenerateFormWindowModel(model);
	return window;
}
