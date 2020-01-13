#include "stdafx.h"
#include "misVolumeSliceMapper.h"

#include "DentalQuadrantFinder.h"
#include "DentalViewSideAnnotationTextBuilder.h"
#include "ICursorService.h"
#include "IRepresentation.h"
#include "mis2DROIActivation.h"
#include "mis3DViewer.h"
#include "misAnnoatationGroupRep.h"
#include "misAnnotationRepresentation.h"
#include "misAutoMeasurment.h"
#include "misColorPointWidget.h"
#include "misCoreEvents.h"
#include "misDistributionEvent.h"
#include "misImageToTexturePropertyConvertor.h"
#include "misMemberCommandCallback.h"
#include "misScrewCompound.h"
#include "misSeedBoundingCalculator.h"
#include "misImagePlaneInformationStrct.h"
#include "mis2DToolActor.h"
#include "misLandamrkListCategorizer.h"
#include "LandmarkVisibilty.h"
#include "misCursorService.h"
#include "misCamera.h"
#include "misLandmarkVisualizer.h"
#include "misLandmarkPointerRepresentation.h"

#pragma warning (disable : 4503)

using namespace std;

void misVolumeSliceMapper::ShowAnnotationDetailOn()
{
	m_ShowAnnotationDetail = true;
}

void misVolumeSliceMapper::ShowAnnotationDetailOff()
{
	m_ShowAnnotationDetail = false;
}

void misVolumeSliceMapper::SetShowAnnotationDetail(bool status)
{
	m_ShowAnnotationDetail = status;
}

bool misVolumeSliceMapper::ShowAnnotationDetail() const
{
	return m_ShowAnnotationDetail;
}

misVolumeSliceMapper::misVolumeSliceMapper(std::shared_ptr<ScrewListType> screws, std::shared_ptr<Iwindows> pWindow, int index, std::shared_ptr<I3DViewer> viewer,
	std::shared_ptr<ICornerProperties> cornerProp,
	std::shared_ptr<IUpdateLandmarkCameraView> m_UpdateLandmarkCameraViewer,
	std::unique_ptr<IInitializeScrewWidget> widgetInitilizer, double differenceForViewingSeed)
	:
	m_ImageAnnotations(std::make_shared<misImageAnnotation>()),
	m_MeasurmentService(misMeasurment::New()),
	m_CameraService(std::make_shared<misCameraInteraction>()),
	m_RealTimeMode(false),
	m_ShowAnnotationDetail(false),
	m_IsOblique(false),
	m_ShowAnnotation(false),
	m_ProstrateState(false),
	m_SurgeryType(ENT),
	m_pcallBack(vtkSmartPointer<misImageCallback>::New()),
	m_pImageStyle(vtkSmartPointer<misInteractorSTyleImageExtend>::New()),
	m_DentalAnnotationBuilder(std::make_shared<parcast::DentalViewSideAnnotationTextBuilder>()),
	m_QuadrantFinder(std::make_shared<parcast::DentalQuadrantFinder>()),
	m_SideAnnotations(std::make_shared<misSideAnnotation>()),
	m_LandmarkVisibilty(std::make_unique < LandmarkVisibilty >(cornerProp, differenceForViewingSeed) ),
	m_currentLandmarkIndex(-1),
	m_CurrentLandmarkType(UnkownLandmarkType),
	m_CurrentLandmarkLableType(NUMERICALLANDMARK),
	m_UpdateLandmark(false),
	m_IsPointWidgetObserverAdded(false),
	m_IsPointSelectObserverAdded(false),
	m_CursorService(std::make_shared<misCursorService>()),
	m_ROIBox(vtkSmartPointer<misROIWidget>::New()),
	m_IsROIActive(false),
	m_3DViewer(viewer)
{
	SetWindow(pWindow, index);
	m_CameraService->SetAutoCameraScale(0);
	m_WidgetFocalPoint[0] = 0;
	m_WidgetFocalPoint[1] = 0;
	m_WidgetFocalPoint[2] = 0;
	misVolumeSliceMapper::SetImageStyle();
}

void misVolumeSliceMapper::AddRepresentation(std::shared_ptr<IRepresentation> pRepresentation)
{
	m_Renderer = m_3DViewer->GetRenderer();
	auto  pStImage = std::dynamic_pointer_cast<misPlanarRepresentation>(pRepresentation);
	if (!(m_3DViewer->CheckNewRepresentationValidity(pRepresentation)))
		return;
	m_3DViewer->AddRepresentation(pRepresentation);

	auto ROIClickCallback = misMemberCommandCallback<misVolumeSliceMapper>::New();
	ROIClickCallback->SetCallbackFunction(this, &misVolumeSliceMapper::ROIClickAction);
	if (!m_ROIBox->HasObserver(misROIWidgetChangeEvent))
		m_ROIBox->AddObserver(misROIWidgetChangeEvent, ROIClickCallback);

	auto ROIChangeCallback = misMemberCommandCallback<misVolumeSliceMapper>::New();
	ROIChangeCallback->SetCallbackFunction(this, &misVolumeSliceMapper::UpdateWidgetBox);
	if (!m_ROIBox->HasObserver(vtkCommand::EndInteractionEvent))
		m_ROIBox->AddObserver(vtkCommand::EndInteractionEvent, ROIChangeCallback);

	auto pointSelectCallback = misMemberCommandCallback<misVolumeSliceMapper>::New();
	pointSelectCallback->SetCallbackFunction(this, &misVolumeSliceMapper::PointSelectAction);
	AddImageOrientation3DModel(pRepresentation);
	m_Renderer->GetActiveCamera()->SetClippingRange(1, 1200);
	if (!pStImage)
		return;
	auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (gpu2DRep)
		GetCornerProperties()->SetObliqueMode(m_IsOblique);
	if (!m_IsPointSelectObserverAdded)
	{
		GetRendererWindowInteractor()->AddObserver(vtkCommand::LeftButtonPressEvent, pointSelectCallback);
		GetRendererWindowInteractor()->AddObserver(vtkCommand::RightButtonPressEvent, pointSelectCallback);
		m_IsPointSelectObserverAdded = true;
	}
	m_MainRepresentation = pStImage;

	IMAGEORIENTATION orientation = pStImage->GetOrientation();
	m_CameraService->SetImageOrientation(orientation);
	m_CameraService->SetCornerProperties(GetCornerProperties());
	m_CameraService->SetCamera(m_Renderer->GetActiveCamera());
	m_CameraService->SetPlaneCenter(pStImage->GetCenter().Elements());
	m_Cornerproperties->SetOrientation(orientation);
	SetInteractionStyleProperties();
	CreateImageAnnotation();
}

void misVolumeSliceMapper::SetImageStyle()
{
	auto  pStImage = std::dynamic_pointer_cast<misPlanarRepresentation> (m_MainRepresentation);
	if (pStImage)
		m_MeasurmentService->SetInteractionStyleExtend(m_pImageStyle, pStImage->GetOrientation());
	m_pImageStyle->AddObserver(vtkCommand::WindowLevelEvent, m_pcallBack);
	m_pImageStyle->AddObserver(vtkCommand::StartWindowLevelEvent, m_pcallBack);
	m_pImageStyle->AddObserver(vtkCommand::EndWindowLevelEvent, m_pcallBack);
	m_pImageStyle->AddObserver(vtkCommand::ResetWindowLevelEvent, m_pcallBack);
}

void misVolumeSliceMapper::SetWindow(std::shared_ptr<Iwindows> pWindow, int index)
{
	m_IndexInGroup = index;
	m_3DViewer->SetWindow(pWindow, index);
	m_Renderer = m_3DViewer->GetRenderer();
	m_MeasurmentService->SetRenderWindowInteractor(GetRendererWindowInteractor());
	m_Renderer->GetActiveCamera()->SetClippingRange(1, 1200);
}

void misVolumeSliceMapper::SetDefaultWindowLevel(void)
{
	m_pImageStyle->InvokeEvent(vtkCommand::ResetWindowLevelEvent);
}

void misVolumeSliceMapper::SetImageContrast(misPlaneEnum planeIndex)
{
	if (!m_MainRepresentation)
		return;
	auto gpu2DRep = std::dynamic_pointer_cast<misPlanarRepresentation>	(m_MainRepresentation);
	if (!gpu2DRep)
		return;

	auto planes = gpu2DRep->GetPlaneInformation();

	std::shared_ptr<IImage> imageData = gpu2DRep->GetImage(planeIndex);
	misWindowLevelStr winLev;
	if (!imageData)
		return;
	if (!m_pcallBack)
		return;
	auto levWin = imageData->GetImageDataProperties()->GetViewingProperties().GetLevelWindow();
	m_pcallBack->SetCurrentWindowLevel(levWin);
}

void misVolumeSliceMapper::SetInteractionStyleProperties()
{
	if (!m_MainRepresentation)
		return;
	std::shared_ptr<misPlanarRepresentation>  gpu2DRep =
		dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);


	m_pcallBack->SetImageRep(gpu2DRep);
	m_pcallBack->SetDefaultWindowLevel(
		gpu2DRep->GetImage(gpu2DRep->GetPlaneWithMaximumVisibility())->
		GetImageDataProperties()->GetViewingProperties().GetInitialLevelWindow());
	int* sizeWindow = m_Renderer->GetSize();
	m_pcallBack->SetSize(sizeWindow);
	vtkRenderWindowInteractor*  pInteractor = GetRendererWindowInteractor()/*GetRenderer()->GetRenderWindow()->GetInteractor()*/;
	pInteractor->SetInteractorStyle(m_pImageStyle);
	misMemberCommandCallback<misVolumeSliceMapper>* callback = misMemberCommandCallback<misVolumeSliceMapper>::New();
	callback->SetCallbackFunction(this, &misVolumeSliceMapper::InteractionStyleCallback);
	if (!m_pImageStyle->HasObserver(misGoNextImageEvent))
		m_pImageStyle->AddObserver(misGoNextImageEvent, callback);
	if (!m_pImageStyle->HasObserver(misSetMeasurmentWidgetEvent))
		m_pImageStyle->AddObserver(misSetMeasurmentWidgetEvent, callback);
	if (!m_pImageStyle->HasObserver(misPanImageEvent))
		m_pImageStyle->AddObserver(misPanImageEvent, callback);
}

misImageCallback *misVolumeSliceMapper::GetImageCallBack()
{
	return m_pcallBack;
}


void misVolumeSliceMapper::UpdateDentalSideAnnotationsBuilder()
{
	auto const trans = m_Cornerproperties->GetTransform();
	double zAxis[] = { 0, 0, 1, 0 };
	auto const planDir = trans->MultiplyDoublePoint(zAxis);

	const auto panoCoordConverter = m_Cornerproperties->GetPanoramicCoordinateConverter();
	m_DentalAnnotationBuilder->SetHasCurve(IsDentalSpecialViewsEnabled());

	auto const quadrant = m_QuadrantFinder->GetQuadrant(
		panoCoordConverter, m_IsOblique, parcast::VectorD3(planDir), GetDentalSurgeryType());
	m_DentalAnnotationBuilder->SetDentalQuadrant(quadrant);
}

void misVolumeSliceMapper::CreateImageAnnotation(void)
{
	if (m_ImageAnnotations)
		RemoveRepresentation(m_ImageAnnotations);
	if (m_SideAnnotations)
		RemoveRepresentation(m_SideAnnotations);
	m_ImageAnnotations = std::make_shared<misImageAnnotation>();
	const auto windowSize = m_Renderer->GetRenderWindow()->GetSize();
	auto showSideAnnotation = m_ShowAnnotationDetail || m_ShowAnnotation;

	UpdateDentalSideAnnotationsBuilder();

	m_AnnotationUpdater.UpdateAnnotations(m_ImageAnnotations, m_SideAnnotations, m_DentalAnnotationBuilder,
		GetOrientationDirection(), m_ViewPort, windowSize[0] * m_ViewPort.Width(), windowSize[1],
		m_Cornerproperties->GetImagePlaneOffset(),
		m_IndexInGroup, showSideAnnotation, m_ProstrateState, m_SurgeryType, m_IsOblique, IsDentalSpecialViewsEnabled());

	AddRepresentation(m_ImageAnnotations);

	if (showSideAnnotation)
	{
		AddRepresentation(m_SideAnnotations);
	}
}



int misVolumeSliceMapper::GetNumberOfRepresentations()
{
	return m_3DViewer->GetNumberOfRepresentations();
}

std::shared_ptr<misPlanarRepresentation> misVolumeSliceMapper::GetImageRprensentaion()
{
	return  std::dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);

}

 

void misVolumeSliceMapper::SetWidgetFocalPoint(const double* pos)
{
	m_WidgetFocalPoint[0] = pos[0];
	m_WidgetFocalPoint[1] = pos[1];
	m_WidgetFocalPoint[2] = pos[2];
}

void misVolumeSliceMapper::GetWidgetFocalPoint(double pos[3])
{
	pos[0] = m_WidgetFocalPoint[0];
	pos[1] = m_WidgetFocalPoint[1];
	pos[2] = m_WidgetFocalPoint[2];
}

void misVolumeSliceMapper::ReleaseImageResource()
{
	m_MeasurmentService->ResetMeasurmentWidget();
	SetControlToPan();
	ResetGeneralToolbarState();
	std::shared_ptr<misRepresentation> imagePlane, annotation;
	for (auto pRep : m_3DViewer->GetRepresentations())
	{
		auto pImmagePlane = std::dynamic_pointer_cast<misPlanarRepresentation>(pRep);
		if (pImmagePlane)
			imagePlane = pImmagePlane;
		auto pAnnotation = std::dynamic_pointer_cast<misAnnotationRepresentation>(pRep);
		if (pAnnotation)
			annotation = pAnnotation;
	}
	if (imagePlane)
		RemoveRepresentation(imagePlane);
	if (annotation)
		RemoveRepresentation(annotation);


	if (m_ImageAnnotations)
	{
		RemoveRepresentation(m_ImageAnnotations);
		m_ImageAnnotations = nullptr;
	}
	m_IsPointSelectObserverAdded = false;
	m_IsPointWidgetObserverAdded = false;
	m_Cornerproperties->Reset();
	m_MainRepresentation.reset();


}





void misVolumeSliceMapper::UpdateWindowSize(misStrctWindowSize &size)
{
	CreateImageAnnotation();
}

vtkRenderWindowInteractor* misVolumeSliceMapper::GetRendererWindowInteractor()
{
	return m_3DViewer->GetWindow()->GetInterActor();
}

std::shared_ptr<misCameraInteraction> misVolumeSliceMapper::GetCameraService()
{
	return m_CameraService;
}

bool misVolumeSliceMapper::ChangeMeasurmentMode(MEASURMENTMODE measurmentMode)
{
	bool res = false;
	if (m_MeasurmentService)
	{
		auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
		if (gpu2DRep)
		{
			switch (measurmentMode)
			{
			case NORMALMEASURMENT:
			{
				m_MeasurmentService = misMeasurment::New();
				m_MeasurmentService->SetInteractionStyleExtend(m_pImageStyle, gpu2DRep->GetOrientation());
				m_MeasurmentService->SetRenderWindowInteractor(GetRendererWindowInteractor());
				res = true;
				break;
			}
			case AUTOMEASURMENT:
			{
				m_MeasurmentService = misAutoMeasurment::New();
				misAutoMeasurment * tempMeasurment = dynamic_cast<misAutoMeasurment *>(m_MeasurmentService.GetPointer());
				if (NULL != tempMeasurment)
				{
					tempMeasurment->SetInteractionStyleExtend(m_pImageStyle, gpu2DRep->GetOrientation());
					tempMeasurment->SetRenderWindowInteractor(GetRendererWindowInteractor());
					tempMeasurment->SetImageOrientation(gpu2DRep->GetOrientation());
					res = true;
				}
			}
			}
		}
	}
	return res;
}

void misVolumeSliceMapper::Render()
{
	try
	{
		if (m_Renderer && m_MainRepresentation)
		{
			auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
			if (gpu2DRep)
			{
				m_CameraService->UpdateView();
				m_LandmarkVisibilty->CheckVisibility(m_landMarkList);
				UpdateViewROIBox();
			}
		}

	}

	catch (const std::exception& e)
	{
		std::stringstream errorMessage;
		errorMessage << "Exception thrown in the rendering pipeline - misImageViewer::Render(). Exception message: " <<
			e.what() << std::endl;
		std::cout << errorMessage.str();
		/*if (GetLogger())
			GetLogger()->Error(errorMessage.str());*/
	}
	catch (...)
	{
		std::string errorMessage("Exception of unknown type thrown in the rendering pipeline - misImageViewer::Render().");
		std::cout << errorMessage;
		/*if (GetLogger())
			GetLogger()->Error(errorMessage);*/
	}
	//IMORTANT NOTE: render must be called after update Camera!
	m_3DViewer->Render();
}

void misVolumeSliceMapper::ResetGeneralToolbarInRightClick()
{
	misAutoMeasurment* tempMeasurment = dynamic_cast<misAutoMeasurment *>(m_MeasurmentService.GetPointer());
	if (NULL != tempMeasurment)
	{
		misResetAutoMeasurmentButtomCore ev2;
		ev2.SetSequenceName(GetWindow()->GetParentTabName());
		ev2.SetSubTab(GetWindow()->GetParentSubTabName());
		IVolumeSlicer::InvokeEvent(ev2);

	}

	ResetGeneralToolbarState();
}

void misVolumeSliceMapper::ResetGeneralToolbarState()
{

	misChangeButtomStateCore ev;
	ev.Set(PANSTATE);
	ev.SetSequenceName(GetWindow()->GetParentTabName());
	ev.SetSubTab(GetWindow()->GetParentSubTabName());
	IVolumeSlicer::InvokeEvent(ev);

}

void misVolumeSliceMapper::SetControlToPan()
{
	m_pImageStyle->SetSatateToRender();
}

void misVolumeSliceMapper::UpdateImageInteractionState()
{
	SetGeneralToolbarState(PANSTATE);
	GetMeasurmentService()->ResetMeasurmentWidget();
}

 

void misVolumeSliceMapper::FindProperDirection(double direction[3], double position[3])
{

	if (m_MainRepresentation)
	{
		auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
		if (gpu2DRep)
		{
			IMAGEORIENTATION  orient = gpu2DRep->GetOrientation();
			switch (orient)
			{
			case  AXIAL:
				direction[0] = 1; direction[1] = 1; direction[2] = 5;
				break;

			case CORONAL:
				direction[0] = 1; direction[1] = 5; direction[2] = 1;
				break;

			case SAGITTAL:
				direction[0] = -5; direction[1] = 1; direction[2] = 1;
				break;
			}
		}
	}
}

void misVolumeSliceMapper::SetLandmarkPosition(int index, const double position[3])
{
	auto size = m_landMarkList.size();
	if ((index >= 0) && (index < size))
	{
		for (int i = 0; i < m_landMarkList.size(); i++)
		{
			if (m_landMarkList[i]->IsValid())
			{
				if (i == index)
				{
					m_landMarkList[i]->UpdateAsSelected();
					m_landMarkList[i]->SetPosition(position);
					m_landMarkList[i]->SetLabelData(i + 1, SELECTED, m_CurrentLandmarkLableType);
					m_landMarkList[i]->Validate();
				}
				else
				{
					m_landMarkList[i]->UpdateNormal();
				}
			}
		}
	}
}

void misVolumeSliceMapper::UpdateLandmarkPosition()
{
	misMoveLandmarkWithitsWidget ev;
	misSimplePointType s;
	s.data[0] = m_WidgetFocalPoint[0];
	s.data[1] = m_WidgetFocalPoint[1];
	s.data[2] = m_WidgetFocalPoint[2];

	ev.Set(s);
	IVolumeSlicer::InvokeEvent(ev);
}

misSimplePointListType misVolumeSliceMapper::GetLandmarkList(misLandmarkType seedType )
{
	auto pRep = std::dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	std::shared_ptr<IImage> pImage = pRep->GetImage();
	auto imageGeo = std::make_shared<misImageGeoProperties>(pImage->GetRawImageData());
	auto categorizer = std::make_unique<misLandamrkListCategorizer>(imageGeo);
	return categorizer->GetLandamrks(seedType, m_landMarkList, pImage);
}



void misVolumeSliceMapper::UpdateImage(bool updateCamera/*=true*/)
{

	auto pos = m_Cornerproperties->GetCurrentPosition();
	if (updateCamera)
		m_Cornerproperties->ResetSightLineIntersectionPoint();
	m_CursorService->UpdateWidgetPosition();
	SetWidgetFocalPoint(pos.Elements());
}

void misVolumeSliceMapper::InteractionStyleCallback(vtkObject *caller, unsigned long eventId, void* callData)
{

	if (eventId == misGoNextImageEvent)
	{
		int* stp = (int*)callData;
		int step = *stp;

		int sliceIndex, newSliceIndex, maxSliceIndex;
		std::shared_ptr<IRepresentation> tempRep = m_MainRepresentation;
		if (tempRep)
		{
			auto  gpu2DRep = std::dynamic_pointer_cast<misPlanarRepresentation>(tempRep);
			if (gpu2DRep)
			{
				sliceIndex = m_Cornerproperties->GetCurrentSliceNumber();
				maxSliceIndex = m_Cornerproperties->GetMaxSliceNumber();
				newSliceIndex = sliceIndex + step;

				if (newSliceIndex > -1 && newSliceIndex < maxSliceIndex)
				{
					m_Cornerproperties->SetPositionBySliceNumber(newSliceIndex);
					misUpdatePositionEvent  ev;
					misUpdatePositionInfoStruct infoStr;
					infoStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
					infoStr.IsCameraUpdate = true;
					ev.Set(infoStr);
					IVolumeSlicer::InvokeEvent(ev);
					UpdateImage(false);

				}
			}
		}
	}
	else if (eventId == misSetMeasurmentWidgetEvent)
	{
		MEASURMENTMODE* msrmt = (MEASURMENTMODE*)callData;
		MEASURMENTMODE measurementmode = *msrmt;

		if (measurementmode == NORMALMEASURMENT)
		{
			GetMeasurmentService()->ResetMeasurmentWidget();
			ChangeMeasurmentMode(NORMALMEASURMENT);
			GetMeasurmentService()->SetMeasurmentWidget();
		}
		else if (measurementmode == AUTOMEASURMENT)
		{
			GetMeasurmentService()->ResetMeasurmentWidget();
			ChangeMeasurmentMode(AUTOMEASURMENT);
			double pos[3];
			GetWidgetFocalPoint(pos);
			misAutoMeasurment *tempMeasurment = dynamic_cast<misAutoMeasurment *>(GetMeasurmentService());
			if (NULL != tempMeasurment)
			{
				tempMeasurment->SetWidgetFirstPoint(pos);
				tempMeasurment->SetMeasurmentWidget();
			}
			ResetGeneralToolbarState();
		}
	}
	else if (eventId == misPanImageEvent)
	{
		PanImage();
		return;

	}
}

double* misVolumeSliceMapper::CalculateNewPosition(vtkRenderWindowInteractor * interactor)
{
	double* position = 0;
	auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (!gpu2DRep)
		return position;
	int x = 0;
	int y = 0;
	interactor->GetEventPosition(x, y);
	vtkRenderer* pRenderer = interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
	pRenderer->SetDisplayPoint(x, y, 0);
	pRenderer->DisplayToWorld();
	position = pRenderer->GetWorldPoint();
	double* cameraRange = m_CameraService->GetCamera()->GetClippingRange();
	const double distanceToPlane = m_Cornerproperties->GetCameraDistanceToPlane();
	double Distance = (distanceToPlane - cameraRange[0]);
	misSimplePointType planeNorm = m_Cornerproperties->GetPlaneNormal();
	misSimplePointType wordPosition;
	wordPosition.SetPoint(position);
	planeNorm.Normalize();
	planeNorm.Multiply(-Distance);
	wordPosition.Sum(planeNorm);
	wordPosition.GetPoint(position);
	double bounds[6];
	gpu2DRep->GetBoundingBox(bounds);
	if ((position[0] > bounds[1]) || (position[1] > bounds[3]) || (position[2] > bounds[5]))
	{
		return 0;
	}
	else if ((position[0] < bounds[0]) || (position[1] < bounds[2]) || (position[2] < bounds[4]))
	{
		return 0;
	}
	return position;
}

void misVolumeSliceMapper::PointSelectAction(vtkObject *caller, unsigned long eventId, void* callData)
{
	if (!m_MainRepresentation || !m_CameraService->GetCamera() || !m_Cornerproperties->GetTransform())
		return;

	InteractionState state = GetInteractionState();
	if (eventId == vtkCommand::LeftButtonPressEvent)
	{
		if (state == WidgetInteractionState)
		{
			UpdateImageWithSelectedPoint();
			return;
		}
	}
	if (eventId == vtkCommand::RightButtonPressEvent)
	{
		m_LastMouseEventX = -1;
		m_LastMouseEventY = -1;
		if (state == WidgetInteractionState)
			m_pImageStyle->SetStateToPan();
		else

		{
			BackToPanModeByRightClick();
			misBackToPanModeEvent ev;
			IVolumeSlicer::InvokeEvent(ev);
			return;
		}
	}


}

void misVolumeSliceMapper::UpdateImageWithSelectedPoint()
{

	auto interactor = dynamic_cast<vtkRenderWindowInteractor*> (GetRendererWindowInteractor());
	double* position = CalculateNewPosition(interactor);
	if (!position)
	{
		m_Cornerproperties->SetSightLineIntersectionPointToPlaneCenter();
		return;
	}

	m_Cornerproperties->SetCurrentPosition(position);

	misUpdatePositionEvent ev;
	misUpdatePositionInfoStruct updateStr;
	updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
	updateStr.IsCameraUpdate = true;
	ev.Set(updateStr);
	IVolumeSlicer::InvokeEvent(ev);

	bool isCameraUpdate = false;
	if (m_CaptureLandmark)
	{
		CaptureLandmark(position);
		isCameraUpdate = true;
	}
	UpdateImage(isCameraUpdate);
}

vtkProp3D* misVolumeSliceMapper::GetWidgetBoundedActor()
{
	vtkProp3D* widgetActor = NULL;
	auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (gpu2DRep)
	{
		widgetActor = gpu2DRep->GetQuadPlane();
	}
	return widgetActor;
}


void misVolumeSliceMapper::CaptureLandmark(double* position)
{
	int currentIndex;

	if (m_currentLandmarkIndex == -1)
	{
		currentIndex = AddNextLandmark(position, m_CurrentLandmarkType, m_CurrentLandmarkLableType);
	}
	else
	{
		currentIndex = m_currentLandmarkIndex;
		AddLandmark(currentIndex, position, m_CurrentLandmarkType, m_CurrentLandmarkLableType);
	}
	if (currentIndex != -1)
	{
		misLandmarkInfoStruct landmarkStr;
		landmarkStr.Landmarktype = m_CurrentLandmarkType;
		landmarkStr.CurrentPosition = position;
		landmarkStr.landmarkIndex = currentIndex;
		landmarkStr.landmarkLableType = m_CurrentLandmarkLableType;
		landmarkStr.validity = true;
		misAddLandmarkEvent landmarkEv;
		landmarkEv.Set(landmarkStr);
		IVolumeSlicer::InvokeEvent(landmarkEv);
	}

	m_CurrentLandmarkType = UnkownLandmarkType;
	m_currentLandmarkIndex = -1;
	m_CaptureLandmark = false;
	m_CursorService->Set3DInteractionCapturedFlag(true);
}

void misVolumeSliceMapper::WidgetChangeAction(vtkObject *caller, unsigned long eventId, void* callData)
{
	if (eventId == vtkCommand::EndInteractionEvent)
	{
		InteractionState state = GetInteractionState();

		if (m_Cornerproperties->GetTransform() == 0)
		{
			/*if (GetLogger())
			{
				GetLogger()->SetPriorityLevel(itk::LoggerBase::CRITICAL);
				(*GetLogger()) << "misImageViewer::WidgetChangeAction->Corner transform is zero!";
			}*/
			return;
		}

		if ((state == ContrastState) || (state == MeasurmentInteractionState) || (state == AutoMeasurmentInteractionState))
		{

			misUpdatePositionEvent ev;
			misUpdatePositionInfoStruct updateStr;
			updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
			updateStr.IsCameraUpdate = true;
			ev.Set(updateStr);
			IVolumeSlicer::InvokeEvent(ev);
			return;
		}

		misColorPointWidget *pointWidget = dynamic_cast<misColorPointWidget*>(caller);
		if (pointWidget)
		{
			double  pos[3];
			pointWidget->GetPosition(pos);
			m_Cornerproperties->SetCurrentPosition(pos);

			misUpdatePositionEvent ev;
			misUpdatePositionInfoStruct updateStr;
			updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
			updateStr.IsCameraUpdate = true;
			ev.Set(updateStr);
			IVolumeSlicer::InvokeEvent(ev);

			if (m_currentLandmarkIndex != -1)
			{
				//if (m_UpdateLandmark)
				//{
				SetLandmarkPosition(m_currentLandmarkIndex, pos);

				misLandmarkInfoStruct evData;
				evData.CurrentPosition = pos;
				evData.landmarkIndex = m_currentLandmarkIndex;
				evData.Landmarktype = m_CurrentLandmarkType;
				evData.landmarkLableType = m_CurrentLandmarkLableType;

				misAddLandmarkEvent ev;
				ev.Set(evData);
				IVolumeSlicer::InvokeEvent(ev);

				m_UpdateLandmark = false;
				//m_CurrentLandmarkType  = UnkownLandmarkType;
				//m_currentLandmarkIndex = -1;
				//}
			}
		}
	}
}

void misVolumeSliceMapper::InitializeWidget(misCursorType widgetType)
{
	m_CursorService->SetWidgetType(widgetType);
	m_CursorService->CreateWidget();
	auto  mainGPURep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (mainGPURep)
	{
		double bound[6];
		GetWidgetBoundingBox(bound);
		m_CursorService->SetWidgetBounds(bound);
		m_CursorService->SetCornerProperties(m_Cornerproperties);
		m_CameraService->SetCornerProperties(m_Cornerproperties);
		misMemberCommandCallback<misVolumeSliceMapper>* widgetChangeCallback = misMemberCommandCallback<misVolumeSliceMapper>::New();
		widgetChangeCallback->SetCallbackFunction(this, &misVolumeSliceMapper::WidgetChangeAction);
		if (!m_IsPointWidgetObserverAdded)
		{
			m_CursorService->AddObserver(widgetChangeCallback);
			m_IsPointWidgetObserverAdded = true;
		}
	}
	m_CursorService->SetWidgetInteractor((vtkRenderWindowInteractor*)m_Renderer->GetRenderWindow()->GetInteractor());
	m_CursorService->SetRenderer(m_Renderer);
	vtkProp3D* widgetActor = GetWidgetBoundedActor();
	if (widgetActor)
	{
		m_CursorService->ApplyWidget(widgetActor);
		m_CursorService->EnableWidget();
	}
}

void  misVolumeSliceMapper::SetViewingProperties(misPlaneEnum planeIndex, misWindowLevelStr winLevStr)
{
	if (!m_MainRepresentation)
		return;
	auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (gpu2DRep)
	{
		gpu2DRep->SetViewingProperties(planeIndex, winLevStr);
		SetImageContrast(planeIndex);
	}
}

bool misVolumeSliceMapper::ProcessRequest(const itk::EventObject* event)
{
	bool res = false;

	if ((typeid(*event) == typeid(misPlaneContrastEvent)))
	{
		const misPlaneContrastEvent* pEventData = dynamic_cast<const misPlaneContrastEvent*>(event);

		if (pEventData)
		{
			if (m_MainRepresentation)
			{
				auto gpu2DRep = std::dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
				if (gpu2DRep)
				{
					misPlaneIndexWinLevStr ContrastStr = pEventData->Get();
					misWindowLevelStr winLevStr = ContrastStr.WinLev;
					misPlaneEnum planeIndex = ContrastStr.PlaneIndex;
					double planeOpacity = gpu2DRep->GetOpacityValueOfTexture(planeIndex);

					if (planeOpacity > 0.1)
						SetViewingProperties(planeIndex, winLevStr);
					return true;
				}
			}
		}
	}

	else if ((typeid(*event) == typeid(misUpdatePositionEvent)))
	{
		const misUpdatePositionEvent* pEventData = dynamic_cast<const misUpdatePositionEvent*>(event);
		misUpdatePositionInfoStruct info = pEventData->Get();
		m_Cornerproperties->SetMatrix(info.CornerTransform);
		UpdateImage(info.IsCameraUpdate);
		CreateImageAnnotation();
		if (info.ForceToRender)
			Render();
		return true;
	}

	else if ((typeid(*event) == typeid(misAddLandmarkEvent)))
	{
		const misAddLandmarkEvent*	pEventData = dynamic_cast<const misAddLandmarkEvent*>(event);
		misLandmarkInfoStruct		lndmarkStr = pEventData->Get();

		auto position = m_Cornerproperties->GetCurrentPosition();
		AddLandmark(lndmarkStr.landmarkIndex, position.Elements(), lndmarkStr.Landmarktype, lndmarkStr.landmarkLableType);

		m_CaptureLandmark = false;
		m_CursorService->Set3DInteractionCapturedFlag(true);
		m_UpdateLandmark = false;
		m_LandmarkVisibilty->CheckVisibility(m_landMarkList);
		return true;
	}

	else if ((typeid(*event) == typeid(misUpdateLandmarkStatusEvent)))
	{
		const misUpdateLandmarkStatusEvent* pEventData = dynamic_cast<const misUpdateLandmarkStatusEvent*>(event);
		misLandmarkInfoStruct lndmarkStr = pEventData->Get();

		double* position = new double[3];
		position[0] = lndmarkStr.CurrentPosition[0];
		position[1] = lndmarkStr.CurrentPosition[1];
		position[2] = lndmarkStr.CurrentPosition[2];
		SetLandmarkPosition(lndmarkStr.landmarkIndex, position);
		return true;
	}

	else if ((typeid(*event) == typeid(misBackToPanModeEvent)))
	{
		BackToPanModeByRightClick();
		return true;
	}
	else if ((typeid(*event) == typeid(misROIWidgetUpdateEvent)))
	{
		const misROIWidgetUpdateEvent* pEventData = dynamic_cast<const misROIWidgetUpdateEvent*>(event);
		misDataBoundStr NewROIBound = pEventData->Get();
		double* data = new double[6];
		NewROIBound.GetArrayBound(data);
		m_ROIBox->PlaceWidget(data);
		return true;
	}

	else if ((typeid(*event) == typeid(misScrewWidgetUpdateEvent)))
	{
		const misScrewWidgetUpdateEvent* pEventData = dynamic_cast<const misScrewWidgetUpdateEvent*>(event);
		misScrewWidgetData screwWidgetVals = pEventData->Get();
		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			if (screwWidgetVals.GetScrewUID() == (*m_ScrewServiceList)[i]->GetScrewUID())
			{
				(*m_ScrewServiceList)[i]->SetScrewWidget(screwWidgetVals);

				m_Cornerproperties->SetMatrix(screwWidgetVals.GetTransformMatrix());
				m_Cornerproperties->SetCurrentPosition(screwWidgetVals.GetStartPoint().data);
				m_CursorService->UpdateWidgetPosition();
				UpdateImage(true);
				SetObliqueFlag(true);
				CreateImageAnnotation();

				auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
				if (!gpu2DRep)
					return false;
				//IMPORTANT NOTE:This method must call after setting transform matrix to corner properties
				return true;
			}
		}
	}
	return res;
}

void misVolumeSliceMapper::UpdateScrewWidget(vtkObject *caller, unsigned long eventId, void* callData)
{
	misLineWidget2* lineCaller = dynamic_cast<misLineWidget2*>(caller);
	if (!lineCaller)
	{
		return;
	}
	if (m_ScrewServiceList->size() == 0)
	{
		return;
	}

	for (int i = 0; i < m_ScrewServiceList->size(); i++)
	{
		misLineWidget2* tmpLine = (*m_ScrewServiceList)[i]->GetWidget();
		if (lineCaller->GetLineWidgetUID() == tmpLine->GetLineWidgetUID())
		{
			if (eventId == vtkCommand::EndInteractionEvent)
			{
				auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
				if (!gpu2DRep)
					return;
				IMAGEORIENTATION orientation = gpu2DRep->GetOrientation();
				(*m_ScrewServiceList)[i]->CalcTransformMatrix(orientation);

				misScrewWidgetData screwWidgetVal;
				screwWidgetVal.SetStartPoint((*m_ScrewServiceList)[i]->GetPoint1WorldPosition());
				screwWidgetVal.SetEndPoint((*m_ScrewServiceList)[i]->GetPoint2WorldPosition());
				screwWidgetVal.SetInterationType((*m_ScrewServiceList)[i]->GetInteractionType());
				screwWidgetVal.DeepCopyTransformMatrix((*m_ScrewServiceList)[i]->GetTransformMatrix());
				screwWidgetVal.SetScrewUID((*m_ScrewServiceList)[i]->GetScrewUID());

				misScrewWidgetUpdateEvent wchanged;
				wchanged.Set(screwWidgetVal);
				IVolumeSlicer::InvokeEvent(wchanged);

				m_CursorService->UpdateWidgetPosition();
				UpdateImage(true);
				return;
			}
		}
	}
}

void misVolumeSliceMapper::BackToPanModeByRightClick()
{
	UpdateImageInteractionState();
	SetControlToPan();
	ResetGeneralToolbarInRightClick();
}


void misVolumeSliceMapper::ROIClickAction(vtkObject *caller, unsigned long eventId, void *callData)
{
	if (eventId == misROIWidgetChangeEvent)
	{
		if (m_Cornerproperties->GetTransform() == 0)
		{
			return;
		}

		IMAGEORIENTATION* orient = (IMAGEORIENTATION*)callData;
		double* ROIPosition = GetROICompressData();
		double pos[3];
		pos[0] = (ROIPosition[0] + ROIPosition[1]) / 2;
		pos[1] = (ROIPosition[2] + ROIPosition[3]) / 2;
		pos[2] = (ROIPosition[4] + ROIPosition[5]) / 2;

		auto gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
		if (gpu2DRep)
		{
			if (*orient == gpu2DRep->GetOrientation())
			{
				m_Cornerproperties->SetCurrentPosition(pos);
				UpdateImage(true);
				misUpdatePositionEvent ev;
				misUpdatePositionInfoStruct updateStr;
				updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
				updateStr.IsCameraUpdate = true;
				ev.Set(updateStr);
				IVolumeSlicer::InvokeEvent(ev);
			}
		}
	}
}

void misVolumeSliceMapper::SetROI(const double* radius)
{
	SetROIInteractor();
	m_ROIBox->SetPlaceFactor(1);
	m_ROIBox->OutlineCursorWiresOff();
	m_ROIBox->RotationEnabledOff();
	auto gpu2DRep = std::dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (gpu2DRep)
	{
		m_ROIBox->SetOrientation(gpu2DRep->GetOrientation());
		double roiData[6];
		std::copy(radius, radius + 6, roiData);
		misROI roi(radius);
		m_ROIBox->PlaceWidget(roiData);
		SetROIActive();
	}
	m_ROIBox->On();
}

void misVolumeSliceMapper::SetROI(const misROI &data)
{
	SetROI(data.getData());
}

void misVolumeSliceMapper::InitializeCornerProperties()
{
	auto  mainRep2D = std::dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (mainRep2D)
	{
		m_Cornerproperties->SetOrientation(mainRep2D->GetOrientation());
		GetCameraService()->SetCornerProperties(m_Cornerproperties);
		mainRep2D->SetCornerProperties(m_Cornerproperties);
	}
}

void misVolumeSliceMapper::UpdateViewROIBox()
{
	if (!m_IsROIActive)
		return;
	auto CurrentPos = m_Cornerproperties->GetCurrentPosition();
	auto roiData = m_ROIBox->GetCompressData(m_ROIBox->GetPoints());
	misROI roi(roiData);
	mis2DROIActivation activation(roi, m_ROIBox->GetOrientation());
	if (activation.IsActive(CurrentPos))
		m_ROIBox->On();
	else
		m_ROIBox->Off();
}

void misVolumeSliceMapper::SetObliqueFlag(bool isOblique)
{
	m_IsOblique = isOblique;
	auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (gpu2DRep)
		GetCornerProperties()->SetObliqueMode(isOblique);
}

void misVolumeSliceMapper::SetOrientationDirection(IMAGEORIENTATION newOrientation)
{
	m_Cornerproperties->SetOrientation(newOrientation);
	m_CameraService->SetImageOrientation(newOrientation);
	auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (!gpu2DRep)
		return;
	gpu2DRep->SetOrientation(newOrientation);
	double bound[6];
	GetWidgetBoundingBox(bound);
	m_CursorService->SetWidgetBounds(bound);
	m_CursorService->SetImageOrientation(newOrientation);
	m_CursorService->ApplyWidget(gpu2DRep->GetQuadPlane());
	UpdateImage();
}

void misVolumeSliceMapper::CalculateInitialScrewTransform(misScrewWidgetData initVals)
{
	for (int i = 0; i < m_ScrewServiceList->size(); i++)
	{
		if (initVals.GetScrewUID() == (*m_ScrewServiceList)[i]->GetScrewUID())
		{
			(*m_ScrewServiceList)[i]->CalcTransformMatrix(SAGITTAL);
			misScrewWidgetData screwWidgetVals;
			screwWidgetVals = initVals;
			screwWidgetVals.DeepCopyTransformMatrix((*m_ScrewServiceList)[i]->GetTransformMatrix());
			m_Cornerproperties->SetMatrix(screwWidgetVals.GetTransformMatrix());
			m_CursorService->UpdateWidgetPosition();
			misUpdatePositionEvent  ev;
			misUpdatePositionInfoStruct infoStr;
			infoStr.IsCameraUpdate = true;
			infoStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
			ev.Set(infoStr);
			IVolumeSlicer::InvokeEvent(ev);
		}
	}
}

void misVolumeSliceMapper::PanImage()
{
	// Calculate previous and current point in world space when moving the mouse pointer while dragging (start and end of panning).
	// Calculate a vector from these points and then move the SightLineIntersectionPoint along this vector.
	auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (!gpu2DRep)
		return;	// No panning when the main representation is not of GPU representation type.

	misTexturePropertyStruct Prop = gpu2DRep->GetImageProperties(FirstImage, MainImage);
	if (!Prop.IsValid())
		return;

	itk::Point<double, 3> panDestination, panOrigin;
	int x = 0, y = 0;
	int deltaX = 0, deltaY = 0;
	GetRendererWindowInteractor()->GetEventPosition(x, y);
	if (m_LastMouseEventX == x && m_LastMouseEventY == y)
		return;
	if (m_LastMouseEventX == -1 && m_LastMouseEventY == -1)
	{
		m_LastMouseEventX = x;
		m_LastMouseEventY = y;
		return;
	}
	m_Renderer->SetDisplayPoint(x, y, 0);
	m_Renderer->DisplayToWorld();
	double* pos = m_Renderer->GetWorldPoint();
	panDestination[0] = pos[0];
	panDestination[1] = pos[1];
	panDestination[2] = pos[2];
	m_Renderer->SetDisplayPoint(m_LastMouseEventX, m_LastMouseEventY, 0);
	m_Renderer->DisplayToWorld();
	pos = m_Renderer->GetWorldPoint();
	panOrigin[0] = pos[0];
	panOrigin[1] = pos[1];
	panOrigin[2] = pos[2];
	m_LastMouseEventX = x;
	m_LastMouseEventY = y;
	// When panning starts at origin and ends in destination, in fact the camera must be moved in the opposite direction to mimic
	// the panning movement.
	itk::Vector<double, 3> panVector = panOrigin - panDestination;
	misSimplePointType previousSightLineIntersectionPoint = m_Cornerproperties->GetSightLineIntersectionPoint();
	itk::Point<double, 3> newSightLineIntersectionPoint;
	newSightLineIntersectionPoint = previousSightLineIntersectionPoint.GetItkPoint() + panVector;
	m_Cornerproperties->SetSightLineIntersectionPointTo(newSightLineIntersectionPoint.GetDataPointer());
}

void misVolumeSliceMapper::ApplyOffset(double offset)
{
	m_Cornerproperties->ApplyOfsset(offset);
}

void misVolumeSliceMapper::SetImageSliceViewerZoomFactor(double zoomFactor)
{
	m_Cornerproperties->SetImageSliceViewerZoomFactor(zoomFactor);
}

void misVolumeSliceMapper::ResetZoom()
{
	auto zoomstr = m_CameraService->Reset2DZoom();
	misChangeZoomPercentageCore ev;
	ev.Set(zoomstr);
	ev.SetSequenceName(GetWindow()->GetParentTabName());
	ev.SetSubTab(GetWindow()->GetParentSubTabName());
	IVolumeSlicer::InvokeEvent(ev);
}

IMAGEORIENTATION misVolumeSliceMapper::GetOrientationDirection()
{
	auto  pStImage = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (!pStImage)
		return UNKnownDirection;
	return pStImage->GetOrientation();
}

void misVolumeSliceMapper::SetInteractionMode(INTERACTIONMODE mode)
{
	m_pImageStyle->SetInteractionMode(mode);
}

void misVolumeSliceMapper::ResetContrast()
{
	auto  gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (!gpu2DRep)
		return;
	m_pcallBack->SetDefaultWindowLevel(
		gpu2DRep->GetImage(gpu2DRep->GetPlaneWithMaximumVisibility())->
		GetImageDataProperties()->GetViewingProperties().GetInitialLevelWindow());
	m_pImageStyle->SetStateToResetContrast();
}

misMeasurment* misVolumeSliceMapper::GetMeasurmentService()
{
	return m_MeasurmentService;
}

InteractionState misVolumeSliceMapper::GetInteractionState() const
{
	return m_pImageStyle->GetInteractionState();
}

void misVolumeSliceMapper::SetInteractionState(InteractionState val)
{
	m_pImageStyle->SetInteractionState(val);
}

misGeneralToolbarState misVolumeSliceMapper::GetGeneralToolbarState() const
{
	return m_GeneralToolbarState;
}

void misVolumeSliceMapper::SetGeneralToolbarState(const misGeneralToolbarState &generalToolbarState)
{
	m_GeneralToolbarState = generalToolbarState;
}

void misVolumeSliceMapper::ResetViewer()
{
	m_Renderer = m_3DViewer->GetRenderer();
	m_Renderer->RemoveAllViewProps();
	DeleteAllScrews();
	ReleaseImageResource();
}

void misVolumeSliceMapper::SetAnnotationEnabled(bool showEnable)
{
	m_ShowAnnotation = showEnable;
}

void misVolumeSliceMapper::SetProstrateState(bool prostrator)
{
	m_ProstrateState = prostrator;
}

void misVolumeSliceMapper::SetSurgeryType(misApplicationType surgeryType)
{
	m_SurgeryType = surgeryType;
	if (m_SurgeryType == Dental)
		SetShowAnnotationDetail(true);
}

misGeneralToolbarState misVolumeSliceMapper::ApplyMeasurment(misGeneralToolbarState ls)
{
	misGeneralToolbarState state = INITIALSTATE;
	if (ls != GetGeneralToolbarState())
		ls = GetGeneralToolbarState();

	if (ls == MEASURMENTSTATE)
		UpdatePanMode();
	else //if(ls != MEASURMENTSTATE)
	{
		misAutoMeasurment* tempMeasurment = dynamic_cast<misAutoMeasurment*>(GetMeasurmentService());
		if (tempMeasurment)
		{
			tempMeasurment->ResetMeasurmentWidget();
		}
		bool changeRes = ChangeMeasurmentMode(NORMALMEASURMENT);
		if (changeRes)
		{
			GetMeasurmentService()->SetMeasurmentWidget();
			SetGeneralToolbarState(MEASURMENTSTATE);
			SetInteractionState(MeasurmentInteractionState);
			state = MEASURMENTSTATE;
		}
	}
	return state;
}
void misVolumeSliceMapper::UpdatePanMode()
{
	GetMeasurmentService()->ResetMeasurmentWidget();
	SetControlToPan();
	SetInteractionState(WidgetInteractionState);
	SetGeneralToolbarState(PANSTATE);
	ResetGeneralToolbarState();
}

misROI misVolumeSliceMapper::GetSeedBounding(int* dimenstion, double* spacing)
{
	misSimplePointListType tFGSeedList = GetLandmarkList(ForeGroundSeed);
	misSeedBoundingCalculator seedCalculator(tFGSeedList);
	return seedCalculator.GetSeedBounding(dimenstion, spacing);
}

void misVolumeSliceMapper::CheckFlyZone(const std::string& segmentationRegion)
{
	auto anotations = Get3DViewer()->FindRepresentationByName("FlyZone");
	if (anotations.empty())
	{
		auto anotation = std::make_shared<misAnnotationRepresentation>("FlyZone");
		AddRepresentation(anotation);
	}
	else
	{
		for (auto anotation : anotations)
		{
			auto anotationRep = std::dynamic_pointer_cast<misAnnotationRepresentation>(anotation);
			anotationRep->SetText(segmentationRegion.c_str());
			anotationRep->SetPosition(50, 50);
		}
	}
}
void misVolumeSliceMapper::SetRealTimeMode(bool val)
{
	m_RealTimeMode = val;
}

bool misVolumeSliceMapper::GetRealTimeMode() const
{
	return m_RealTimeMode;
}

std::shared_ptr<ICornerProperties> misVolumeSliceMapper::GetCornerProperties() const
{
	return m_Cornerproperties;
}


double* misVolumeSliceMapper::GetLandmarkPosition(const int index)
{
	if (m_landMarkList[index]->IsValid())
	{
		const auto pos = new double[3];
		m_landMarkList[index]->GetPosition(pos);
		return pos;
	}
	return nullptr;
}
std::shared_ptr<IScrewCompound> misVolumeSliceMapper::GetScrewWidgetService(misUID uid)
{
	for (int i = 0; i < m_ScrewServiceList->size(); i++)
	{
		if (uid == (*m_ScrewServiceList)[i]->GetScrewUID())
		{
			return (*m_ScrewServiceList)[i];
		}
	}
	return 0;
}

void misVolumeSliceMapper::LockAllScrews()
{
	SetAllScrewsLocked(true);
}

void misVolumeSliceMapper::UnlockAllScrews()
{
	SetAllScrewsLocked(false);
}

void misVolumeSliceMapper::SetAllScrewsLocked(bool isLocked)
{
	if (m_ScrewServiceList->empty())
		return;

	for (auto screwItr = m_ScrewServiceList->begin(); screwItr != m_ScrewServiceList->end(); screwItr++)
	{
		(*screwItr)->SetLocked(isLocked);
	}
}


void misVolumeSliceMapper::RemoveAllScrewServices()
{
	m_ScrewServiceList->clear();
}
vtkRenderer* misVolumeSliceMapper::GetRenderer()
{
	return m_Renderer;
}
std::shared_ptr<IRepresentation> misVolumeSliceMapper::GetMainRepresentation()
{
	return 	m_MainRepresentation;

}
void misVolumeSliceMapper::SetCurrentLandmarkType(misLandmarkType val)
{
	m_CurrentLandmarkType = val;
	if (m_currentLandmarkIndex >= 0 && val != UnkownLandmarkType)
		m_landMarkList[m_currentLandmarkIndex]->SetCategory(val);
}
std::shared_ptr<ICursorService> misVolumeSliceMapper::GetCursorService()
{
	return m_CursorService;
}

void misVolumeSliceMapper::OnScrew(misUID screwUID)
{
	if (m_ScrewServiceList->size() > 0)
	{
		for (int i = 0; i < m_ScrewServiceList->size(); i++)
		{
			if ((*m_ScrewServiceList)[i]->GetScrewUID() == screwUID)
			{
				(*m_ScrewServiceList)[i]->SetSelected(true);
				(*m_ScrewServiceList)[i]->On();
			}
		}
	}
}
 
unsigned long misVolumeSliceMapper::AddObserver(const itk::EventObject & event, itk::Command *command)
{
	return m_DummyObject->AddObserver(event, command);
}

void misVolumeSliceMapper::InvokeEvent(const itk::EventObject& event)
{
	m_DummyObject->SetViewer(this);
	m_DummyObject->InvokeEvent(event);
}
bool misVolumeSliceMapper::HasObserver(const itk::EventObject & event) const
{
	return m_DummyObject->HasObserver(event);
}
void misVolumeSliceMapper::RemoveRepresentation(std::shared_ptr<IRepresentation> pRepresent)
{
	m_3DViewer->RemoveRepresentation(pRepresent);
	for (const auto& landmark : m_landMarkList)
	{
		if (landmark->GetSurface() == pRepresent)
			landmark->InValidate();
	}
}
void misVolumeSliceMapper::AddImageOrientation3DModel(std::shared_ptr<IRepresentation> pRepresentation)
{
	m_Renderer = m_3DViewer->GetRenderer();
	if (!m_ShowManModel)
		return;

	int numOfActor = pRepresentation->GetNumberOfActors();
	if (numOfActor == 0)
		return;


	vtkProp3D* prop = dynamic_cast<vtkProp3D*>(pRepresentation->GetActor(0));
	if (!prop)
		return;

	m_3DViewer->RemoveRepresentationByName("Man Model");
	double* maninREpresentationPosition = prop->GetCenter();
	m_ManModel->Init(maninREpresentationPosition, m_Renderer);
	m_3DViewer->AddRepresentation(m_ManModel);
}
std::shared_ptr<Iwindows> misVolumeSliceMapper::GetWindow() const
{
	return m_3DViewer->GetWindow();
}
 int misVolumeSliceMapper::AddNextLandmark(const double position[3], misLandmarkType category, LANDMARKLABLETYPE lableType)
{
	misCamera camera(m_3DViewer->GetRenderer()->GetActiveCamera()->GetPosition(), m_3DViewer->GetRenderer()->GetActiveCamera()->GetFocalPoint(),
		m_3DViewer->GetRenderer()->GetActiveCamera()->GetViewUp());
	const parcast::Point<double, 3> point(position);
	misLandmarkVisualizer landmarkVisualizer(
		m_MainRepresentation->GetBoundingBox(), camera, m_landMarkList, category,
		lableType, m_ShowLabels, point, GetTypeDirection());

	AddRepresentation(landmarkVisualizer.GetRepresenTation());
	return landmarkVisualizer.GetIndex();
}

 void misVolumeSliceMapper::AddLandmark(int index, const double position[3], misLandmarkType category, LANDMARKLABLETYPE lableType)
 {
	 if (m_landMarkList[index]->IsValid())
	 {
		 if (m_landMarkList[index]->GetCategory() == category)
		 {
			 SetLandmarkPosition(index, position);
			 const auto boundingBox = m_MainRepresentation->GetBoundingBox();
			 const auto handleLength = m_SettingContainer->GetDouble("RegisterationSetting/LandmarkLableHandleLength");
			 const auto offsetAngle = m_SettingContainer->GetDouble("RegisterationSetting/LandmarkLableAngleOffset");

			 auto lablePosition = GetLablePosition(position, boundingBox, handleLength, offsetAngle);
			 m_landMarkList[index]->SetLabelPosition(lablePosition.Elements());
			 UpdateLandmarkCameraView(index);
			 return;
		 }
	 }
	 AddOrSetNextLandmark(index, position, category, lableType);
 }
 double * misVolumeSliceMapper::GetROICompressData()
 {
	 vtkPoints* p = m_ROIBox->GetPoints();
	 double* compData = m_ROIBox->GetCompressData(p);
	 m_ROIBox->UpdateWidgetData();
	 return compData;
 }

void misVolumeSliceMapper::HideLandmarks()
{
	for (auto& i : m_landMarkList)
	{
		if (i->IsValid())
		{
			i->SetVisibilityOff();
		}
	}
}

int misVolumeSliceMapper::AddOrSetNextLandmark(const double position[3], misLandmarkType category,
	 const LANDMARKLABLETYPE lableType)
 {
	 int index = -1;
	 for (int i = 0; i < m_landMarkList.size(); i++)
	 {
		 if (!(m_landMarkList[i]->IsValid()))
		 {
			 index = i;
			 break;
		 }
	 }
	 if (index == -1)
	 {
		 index = static_cast<int> (m_landMarkList.size());
		 auto emptyPointer = std::make_shared<misLandmarkPointerRepresentation>();
		 emptyPointer->InValidate();
		 m_landMarkList.push_back(emptyPointer);
	 }

	 if (m_landMarkList[index]->IsValid())
	 {
		 SetLandmarkPosition(index, position);
	 }
	 else
	 {
		 AddOrSetNextLandmark(index, position, category, lableType);
	 }
	 return index;
 }



 void misVolumeSliceMapper::UpdateLandmarkCameraView(const int index)
 {
	 if (m_UpdateLandmarkCameraViewer)
		 m_UpdateLandmarkCameraViewer->Update(m_MainRepresentation->GetBoundingBox(), m_landMarkList[index]);
 }
 void misVolumeSliceMapper::DeleteAllScrews()
 {
	 if (m_ScrewServiceList && !m_ScrewServiceList->empty())
	 {
		 for (int i = 0; i < m_ScrewServiceList->size(); i++)
		 {
			 (*m_ScrewServiceList)[i]->SetInteractor(NULL);
		 }
		 m_ScrewServiceList->clear();
	 }
 }

 std::shared_ptr<I3DViewer> misVolumeSliceMapper::Get3DViewer() const
 {
	 return m_3DViewer;
 }

parcast::PointD3 misVolumeSliceMapper::GetLablePosition(const double* position, const itk::BoundingBox<double, 3, double>::Pointer
	 & boundingBox, const double handleLength, const double offsetAngle) const
 {
	 auto lablePositionCalculator = parcast::LandmarkLablePositionCalculator(parcast::PointD3(boundingBox->GetMinimum().GetDataPointer()),
	                                                                         parcast::PointD3(boundingBox->GetMaximum().GetDataPointer()), handleLength, offsetAngle);
	 const auto landmarkPos = parcast::PointD3(position[0], position[1], position[2]);
	 return lablePositionCalculator.GetLabelPosition(landmarkPos, GetTypeDirection());
 }