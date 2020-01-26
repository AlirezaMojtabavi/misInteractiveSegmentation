#include "stdafx.h"
#include "misVolumeSlicer.h"

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
#include "misDistributionEvent.h"
#include "misMemberCommandCallback.h"
#include "misScrewCompound.h"
#include "misImagePlaneInformationStrct.h"
#include "misLandamrkListCategorizer.h"
#include "mis3DVolumeRenderer.h"
#include <misMathUtils.h>
#include "IVolumeSlicerEvents.h"
#include "misChangeZoomPercentageCore.h"
#include "misApplicationSetting.h"
#include "ScrewViewerFactory.h"
#include "PanImage.h"


#pragma warning (disable : 4503)

using namespace std;

misVolumeSlicer::misVolumeSlicer(std::shared_ptr<ScrewListType> screwServiceList, std::shared_ptr<Iwindows> pWindow,
                                 int index,
                                 std::shared_ptr<I3DViewer> viewer,
                                 std::shared_ptr<ICornerProperties> cornerProperties,
                                std::shared_ptr<IInitializeScrewWidget> screwIntilizer,
                                 vtkSmartPointer<misInteractorSTyleImageExtend> interactorStyleImageExtend,
                                 misMeasurment::Pointer measurment, misVolumeRendererContainer::Pointer dummyObject,
                                 std::shared_ptr<ICursorService> cursorService,
                                 std::shared_ptr<IBackToPanMode> backToPanMOde,
                                 double differenceForViewingSeed, std::shared_ptr<misCameraInteraction> cameraInteraction)
	: misVolumeRenderer(viewer, pWindow, index),
	  m_ImageAnnotations(std::make_shared<misImageAnnotation>()),
	  m_MeasurmentService(measurment),
	  m_CameraService(cameraInteraction),
	  m_RealTimeMode(false),
	  m_IsOblique(false),
	  m_ShowAnnotation(false),
	  m_ProstrateState(false),
	  m_SurgeryType(ENT),
	  m_pImageStyle(interactorStyleImageExtend),
	  m_DentalAnnotationBuilder(std::make_shared<parcast::DentalViewSideAnnotationTextBuilder>()),
	  m_QuadrantFinder(std::make_shared<parcast::DentalQuadrantFinder>()),
	  m_SideAnnotations(std::make_shared<misSideAnnotation>()),
	  m_CursorService(cursorService),
	  m_ShowManModel(true),
	  m_ManModel(std::make_shared<misManModelrepresentation>("Man Model")),
	  m_Cornerproperties(cornerProperties),
	  m_DummyObject(dummyObject),
	  m_BackToPanMode(backToPanMOde),
	m_PanImage(std::make_shared<PanImage>(cornerProperties))
{
	SetWindow(pWindow, index);
	m_CameraService->SetAutoCameraScale(0);
	m_WidgetFocalPoint[0] = 0;
	m_WidgetFocalPoint[1] = 0;
	m_WidgetFocalPoint[2] = 0;
	misVolumeSlicer::SetImageStyle();
	m_ScrewViewer = parcast::ScrewViewerFactory::Create(Dimention::_2D, screwIntilizer, screwServiceList,
                                                    m_Cornerproperties, m_DummyObject);
	m_ImageContrastObserver->SetWindowLevel(m_WindowLevelSetting);
	m_DummyObject->SetViewer(static_cast<IVolumeRenderer*>(this));
}

misVolumeRendererContainer::Pointer misVolumeSlicer::GetDummySubject()
{
	return m_DummyObject;
}

void misVolumeSlicer::SetTypeDirection(misViewerTypeDirection direction)
{
	m_ViewerTypeDirection = direction;
	
}

misVolumeSlicer::~misVolumeSlicer()
{

	GetRendererWindowInteractor()->RemoveAllObservers();

}


void misVolumeSlicer::ShowAnnotationDetailOn()
{
	m_ShowAnnotationDetail = true;
}

void misVolumeSlicer::ShowAnnotationDetailOff()
{
	m_ShowAnnotationDetail = false;
}

void misVolumeSlicer::SetShowAnnotationDetail(bool status)
{
	m_ShowAnnotationDetail = status;
}

bool misVolumeSlicer::ShowAnnotationDetail() const
{
	return m_ShowAnnotationDetail;
}

void misVolumeSlicer::AddRepresentation(std::shared_ptr<IRepresentation> pRepresentation)
{
	m_Renderer = m_3DViewer->GetRenderer();
	auto pStImage = std::dynamic_pointer_cast<misPlanarRepresentation>(pRepresentation);
	if (!(m_3DViewer->CheckNewRepresentationValidity(pRepresentation)))
		return;
	m_3DViewer->AddRepresentation(pRepresentation);

	auto ROIClickCallback = misMemberCommandCallback<misVolumeSlicer>::New();
	ROIClickCallback->SetCallbackFunction(this, &misVolumeSlicer::ROIClickAction);
	if (!m_ROIBox->HasObserver(misROIWidgetChangeEvent))
		m_ROIBox->AddObserver(misROIWidgetChangeEvent, ROIClickCallback);

	auto ROIChangeCallback = misMemberCommandCallback<misVolumeSlicer>::New();
	ROIChangeCallback->SetCallbackFunction(this, &misVolumeSlicer::UpdateWidgetBox);
	if (!m_ROIBox->HasObserver(vtkCommand::EndInteractionEvent))
		m_ROIBox->AddObserver(vtkCommand::EndInteractionEvent, ROIChangeCallback);


	AddImageOrientation3DModel(pRepresentation);
	m_Renderer->GetActiveCamera()->SetClippingRange(1, 1200);
	if (!pStImage)
		return;
	const auto gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (gpu2DRep)
		GetCornerProperties()->SetObliqueMode(m_IsOblique);
	AddAllPointSelectObserve();
	m_IsPointSelectObserverAdded = true;
	m_MainRepresentation = pStImage;
	m_ImageContrastObserver->SetImageRep(gpu2DRep);
	m_PanImage->SetMainRepresentation(gpu2DRep);
	m_PanImage->SetInteractor(m_3DViewer->GetWindow()->GetInterActor());
	const auto orientation = pStImage->GetOrientation();
	m_CameraService->SetImageOrientation(orientation);
	m_CameraService->SetCornerProperties(GetCornerProperties());
	m_CameraService->SetCamera(m_Renderer->GetActiveCamera());
	m_CameraService->SetDefaultZoom();
	m_CameraService->SetPlaneCenter(pStImage->GetCenter().Elements());
	m_Cornerproperties->SetOrientation(orientation);
	SetInteractionStyleProperties();
	CreateImageAnnotation();

}

void misVolumeSlicer::SetImageStyle()
{
	auto pStImage = std::dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (pStImage)
		m_MeasurmentService->SetInteractionStyleExtend(m_pImageStyle, pStImage->GetOrientation());
	m_pImageStyle->AddObserver(vtkCommand::WindowLevelEvent, m_ImageContrastObserver);
	m_pImageStyle->AddObserver(vtkCommand::StartWindowLevelEvent, m_ImageContrastObserver);
	m_pImageStyle->AddObserver(vtkCommand::EndWindowLevelEvent, m_ImageContrastObserver);
	m_pImageStyle->AddObserver(vtkCommand::ResetWindowLevelEvent, m_ImageContrastObserver);
}


void misVolumeSlicer::SetDefaultWindowLevel(void)
{
	m_pImageStyle->InvokeEvent(vtkCommand::ResetWindowLevelEvent);
}

void misVolumeSlicer::SetImageContrast(misPlaneEnum planeIndex)
{
	if (!m_MainRepresentation)
		return;
	auto gpu2DRep = std::dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (!gpu2DRep)
		return;

	auto planes = gpu2DRep->GetPlaneInformation();

	std::shared_ptr<IImage> imageData = gpu2DRep->GetImage(planeIndex);
	if (!imageData)
		return;

	auto levWin = imageData->GetImageDataProperties()->GetViewingProperties().GetLevelWindow();
	m_WindowLevelSetting->SetCurrentWindowLevel(levWin);
}

void misVolumeSlicer::SetInteractionStyleProperties()
{
	if (!m_MainRepresentation)
		return;
	std::shared_ptr<misPlanarRepresentation> gpu2DRep =
		dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);


	
	auto image = gpu2DRep->GetImage(gpu2DRep->GetPlaneWithMaximumVisibility());
	m_WindowLevelSetting->SetDefaultWindowLevel(
		image->GetImageDataProperties()->GetViewingProperties().GetInitialLevelWindow());
	int* sizeWindow = m_Renderer->GetSize();

	m_WindowLevelSetting->SetSize(sizeWindow);
	vtkRenderWindowInteractor* pInteractor = GetRendererWindowInteractor()
		/*GetRenderer()->GetRenderWindow()->GetInteractor()*/;
	pInteractor->SetInteractorStyle(m_pImageStyle);
	misMemberCommandCallback<misVolumeSlicer>* callback = misMemberCommandCallback<misVolumeSlicer>::New();
	callback->SetCallbackFunction(this, &misVolumeSlicer::InteractionStyleCallback);
	if (!m_pImageStyle->HasObserver(misGoNextImageEvent))
		m_pImageStyle->AddObserver(misGoNextImageEvent, callback);
	if (!m_pImageStyle->HasObserver(misSetMeasurmentWidgetEvent))
		m_pImageStyle->AddObserver(misSetMeasurmentWidgetEvent, callback);
	if (!m_pImageStyle->HasObserver(misPanImageEvent))
		m_pImageStyle->AddObserver(misPanImageEvent, callback);
}


void misVolumeSlicer::UpdateDentalSideAnnotationsBuilder()
{
	auto const trans = m_Cornerproperties->GetTransform();
	double zAxis[] = {0, 0, 1, 0};
	auto const planDir = trans->MultiplyDoublePoint(zAxis);

	const auto panoCoordConverter = m_Cornerproperties->GetPanoramicCoordinateConverter();
	m_DentalAnnotationBuilder->SetHasCurve(IsDentalSpecialViewsEnabled());

	auto const quadrant = m_QuadrantFinder->GetQuadrant(
		panoCoordConverter, m_IsOblique, parcast::VectorD3(planDir), GetDentalSurgeryType());
	m_DentalAnnotationBuilder->SetDentalQuadrant(quadrant);
}

void misVolumeSlicer::CreateImageAnnotation(void)
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
	                                      GetOrientationDirection(), m_ViewPort, windowSize[0] * m_ViewPort.Width(),
	                                      windowSize[1],
	                                      m_Cornerproperties->GetImagePlaneOffset(),
	                                      m_IndexInGroup, showSideAnnotation, m_ProstrateState, m_SurgeryType,
	                                      m_IsOblique, IsDentalSpecialViewsEnabled());

	AddRepresentation(m_ImageAnnotations);

	if (showSideAnnotation)
	{
		AddRepresentation(m_SideAnnotations);
	}
}


int misVolumeSlicer::GetNumberOfRepresentations()
{
	return m_3DViewer->GetNumberOfRepresentations();
}

std::shared_ptr<I2DRepresetation> misVolumeSlicer::GetImageRprensentaion()
{
	return std::dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
}


void misVolumeSlicer::SetWidgetFocalPoint(const double* pos)
{
	m_WidgetFocalPoint[0] = pos[0];
	m_WidgetFocalPoint[1] = pos[1];
	m_WidgetFocalPoint[2] = pos[2];
}

void misVolumeSlicer::GetWidgetFocalPoint(double pos[3])
{
	pos[0] = m_WidgetFocalPoint[0];
	pos[1] = m_WidgetFocalPoint[1];
	pos[2] = m_WidgetFocalPoint[2];
}

void misVolumeSlicer::ReleaseImageResource()
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


void misVolumeSlicer::UpdateWindowSize(misStrctWindowSize& size)
{
	CreateImageAnnotation();
}



std::shared_ptr<misCameraInteraction> misVolumeSlicer::GetCameraService()
{
	return m_CameraService;
}

std::shared_ptr<parcast::WindowLevelSetting> misVolumeSlicer::GetWindowLevel() const
{
	return m_WindowLevelSetting;
}

bool misVolumeSlicer::ChangeMeasurmentMode(MEASURMENTMODE measurmentMode)
{
	bool res = false;
	if (m_MeasurmentService)
	{
		auto gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
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
					misAutoMeasurment* tempMeasurment = dynamic_cast<misAutoMeasurment *>(m_MeasurmentService.
						GetPointer());
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

void misVolumeSlicer::ResetGeneralToolbarState()
{
	m_BackToPanMode->ResetGeneralToolbarState();
}

void misVolumeSlicer::Render()
{
	try
	{
		if (m_Renderer && m_MainRepresentation)
		{
			auto gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
			if (gpu2DRep)
			{
				m_CameraService->UpdateView();
				UpdateViewROIBox();
			}
		}
	}

	catch (const std::exception& e)
	{
		std::stringstream errorMessage;
		errorMessage << "Exception thrown in the rendering pipeline - misVolumeSlicer::Render(). Exception message: " <<
			e.what() << std::endl;
		std::cout << errorMessage.str();
		/*if (GetLogger())
			GetLogger()->Error(errorMessage.str());*/
	}
	catch (...)
	{
		std::string errorMessage(
			"Exception of unknown type thrown in the rendering pipeline - misVolumeSlicer::Render().");
		std::cout << errorMessage;
		/*if (GetLogger())
			GetLogger()->Error(errorMessage);*/
	}
	//IMORTANT NOTE: render must be called after update Camera!
	m_3DViewer->Render();
}


void misVolumeSlicer::FindProperDirection(double direction[3], double position[3])
{
	if (m_MainRepresentation)
	{
		auto gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
		if (gpu2DRep)
		{
			IMAGEORIENTATION orient = gpu2DRep->GetOrientation();
			switch (orient)
			{
			case AXIAL:
				direction[0] = 1;
				direction[1] = 1;
				direction[2] = 5;
				break;

			case CORONAL:
				direction[0] = 1;
				direction[1] = 5;
				direction[2] = 1;
				break;

			case SAGITTAL:
				direction[0] = -5;
				direction[1] = 1;
				direction[2] = 1;
				break;
			}
		}
	}
}


void misVolumeSlicer::UpdateLandmarkPosition()
{
	misMoveLandmarkWithitsWidget ev;
	misSimplePointType s;
	s.data[0] = m_WidgetFocalPoint[0];
	s.data[1] = m_WidgetFocalPoint[1];
	s.data[2] = m_WidgetFocalPoint[2];

	ev.Set(s);
	InvokeEvent(ev);
}




void misVolumeSlicer::UpdateImage(bool updateCamera/*=true*/)
{
	auto pos = m_Cornerproperties->GetCurrentPosition();
	if (updateCamera)
		m_Cornerproperties->ResetSightLineIntersectionPoint();
	m_CursorService->UpdateWidgetPosition();
	SetWidgetFocalPoint(pos.Elements());
}

void misVolumeSlicer::SetControlToPan()
{
	m_BackToPanMode->SetControlToPan();
}

void misVolumeSlicer::InteractionStyleCallback(vtkObject* caller, unsigned long eventId, void* callData)
{
	if (eventId == misGoNextImageEvent)
	{
		int* stp = (int*)callData;
		int step = *stp;

		int sliceIndex, newSliceIndex, maxSliceIndex;
		std::shared_ptr<IRepresentation> tempRep = m_MainRepresentation;
		if (tempRep)
		{
			auto gpu2DRep = std::dynamic_pointer_cast<misPlanarRepresentation>(tempRep);
			if (gpu2DRep)
			{
				sliceIndex = m_Cornerproperties->GetCurrentSliceNumber();
				maxSliceIndex = m_Cornerproperties->GetMaxSliceNumber();
				newSliceIndex = sliceIndex + step;

				if (newSliceIndex > -1 && newSliceIndex < maxSliceIndex)
				{
					m_Cornerproperties->SetPositionBySliceNumber(newSliceIndex);
					misUpdatePositionEvent ev;
					misUpdatePositionInfoStruct infoStr;
					infoStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
					infoStr.IsCameraUpdate = true;
					ev.Set(infoStr);
					InvokeEvent(ev);
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
			misAutoMeasurment* tempMeasurment = dynamic_cast<misAutoMeasurment *>(GetMeasurmentService());
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
		m_PanImage->Pan();
		
	}
}


vtkProp3D* misVolumeSlicer::GetWidgetBoundedActor()
{
	vtkProp3D* widgetActor = NULL;
	auto gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (gpu2DRep)
	{
		widgetActor = gpu2DRep->GetQuadPlane();
	}
	return widgetActor;
}

void misVolumeSlicer::SetROIActive()
{
	m_IsROIActive = true;
}

void misVolumeSlicer::SetROIInteractor()
{
	m_ROIBox->SetInteractor((vtkRenderWindowInteractor*)(m_3DViewer->GetWindow()->GetInterActor()));
}

void misVolumeSlicer::UpdateWidgetBox(vtkObject* caller, unsigned long eventId, void* callData)
{
	if (eventId != vtkCommand::EndInteractionEvent)
		return;

	double* data = GetROICompressData();
	m_ROIBox->PlaceWidget(data);
	misROIWidgetUpdateEvent wchanged;
	misDataBoundStr ROIBound;
	ROIBound.SetArrayBound(data);
	wchanged.Set(ROIBound);
	InvokeEvent(wchanged);
	Render();
}




void misVolumeSlicer::WidgetChangeAction(vtkObject* caller, unsigned long eventId, void* callData)
{
	if (eventId == vtkCommand::EndInteractionEvent)
	{
		InteractionState state = GetInteractionState();

		if (m_Cornerproperties->GetTransform() == 0)
		{
 			return;
		}

		if ((state == ContrastState) || (state == MeasurmentInteractionState) || (state ==
			AutoMeasurmentInteractionState))
		{
			misUpdatePositionEvent ev;
			misUpdatePositionInfoStruct updateStr;
			updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
			updateStr.IsCameraUpdate = true;
			ev.Set(updateStr);
			InvokeEvent(ev);
			return;
		}

		misColorPointWidget* pointWidget = dynamic_cast<misColorPointWidget*>(caller);
		if (pointWidget)
		{
			double pos[3];
			pointWidget->GetPosition(pos);
			m_Cornerproperties->SetCurrentPosition(pos);

			misUpdatePositionEvent ev;
			misUpdatePositionInfoStruct updateStr;
			updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
			updateStr.IsCameraUpdate = true;
			ev.Set(updateStr);
			InvokeEvent(ev);


		}
	}
}

DentalSurgeryType misVolumeSlicer::GetDentalSurgeryType()
{
	return m_DentalSurgeryType;
}

bool misVolumeSlicer::IsDentalSpecialViewsEnabled() const
{
	return m_DentalSpecialViewEnable;
}

void misVolumeSlicer::InitializeWidget(misCursorType widgetType, double pickingTolerance)
{
	m_CursorService->SetWidgetType(widgetType);
	m_CursorService->CreateWidget(pickingTolerance);
	auto mainGPURep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (mainGPURep)
	{
		double bound[6];
		GetWidgetBoundingBox(bound);
		m_CursorService->SetWidgetBounds(bound);
		m_CursorService->SetCornerProperties(m_Cornerproperties);
		m_CameraService->SetCornerProperties(m_Cornerproperties);
		misMemberCommandCallback<misVolumeSlicer>* widgetChangeCallback = misMemberCommandCallback<misVolumeSlicer>::
			New();
		widgetChangeCallback->SetCallbackFunction(this, &misVolumeSlicer::WidgetChangeAction);
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

void misVolumeSlicer::SetViewingProperties(misPlaneEnum planeIndex, misWindowLevelStr winLevStr)
{
	if (!m_MainRepresentation)
		return;
	auto gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (gpu2DRep)
	{
		gpu2DRep->SetViewingProperties(planeIndex, winLevStr);
		SetImageContrast(planeIndex);
	}
}

bool misVolumeSlicer::ProcessRequest(const itk::EventObject* event)
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

	

	else if ((typeid(*event) == typeid(misBackToPanModeEvent)))
	{
		m_BackToPanMode->Update();
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
		m_ScrewViewer->ProcessUpdateScrewWidget(*pEventData, m_CursorService);
	}
	return res;
}

void misVolumeSlicer::ModifyPlane(misPlanWidget* planWidget, misScrewWidgetData& screwWidgetVal)
{
	auto rep = dynamic_cast<IPlanWidgetRepresentation*>(planWidget->GetRepresentation());
	switch (rep->GetInteractionState())
	{
	case 1:
		screwWidgetVal.SetStartPointModified();
		break;
	case 2:
		screwWidgetVal.SetEndPointModified();
		break;
	default:
		break;
	}
}

void misVolumeSlicer::UpdateScrewWidget(vtkObject* caller, unsigned long eventId, void* callData)
{
	m_ScrewViewer->UpdateScrewWidget(caller, eventId, callData);
}


void misVolumeSlicer::ROIClickAction(vtkObject* caller, unsigned long eventId, void* callData)
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
				InvokeEvent(ev);
			}
		}
	}
}

void misVolumeSlicer::SetROI(const double* radius)
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

void misVolumeSlicer::SetROI(const misROI& data)
{
	SetROI(data.getData());
}

void misVolumeSlicer::InitializeCornerProperties()
{
	auto mainRep2D = std::dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (mainRep2D)
	{
		m_Cornerproperties->SetOrientation(mainRep2D->GetOrientation());
		GetCameraService()->SetCornerProperties(m_Cornerproperties);
		mainRep2D->SetCornerProperties(m_Cornerproperties);
	}
}

void misVolumeSlicer::UpdateViewROIBox()
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

void misVolumeSlicer::SetObliqueFlag(bool isOblique)
{
	m_IsOblique = isOblique;
	auto gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (gpu2DRep)
		GetCornerProperties()->SetObliqueMode(isOblique);
}

void misVolumeSlicer::SetOrientationDirection(IMAGEORIENTATION newOrientation)
{
	m_Cornerproperties->SetOrientation(newOrientation);
	m_CameraService->SetImageOrientation(newOrientation);
	auto gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (!gpu2DRep)
		return;
	gpu2DRep->SetOrientation(newOrientation);
	double bound[6];
	GetWidgetBoundingBox(bound);
	m_CursorService->SetWidgetBounds(bound);
	m_CursorService->SetImageOrientation(newOrientation);
	m_CursorService->ApplyWidget(gpu2DRep->GetQuadPlane());
	CreateImageAnnotation();
	UpdateImage();
}



void misVolumeSlicer::ApplyOffset(double offset)
{
	m_Cornerproperties->ApplyOfsset(offset);
}

void misVolumeSlicer::SetImageSliceViewerZoomFactor(double zoomFactor)
{
	m_Cornerproperties->SetImageSliceViewerZoomFactor(zoomFactor);
}

void misVolumeSlicer::ResetZoom()
{
	auto zoomstr = m_CameraService->Reset2DZoom();
	misChangeZoomPercentageCore ev;
	ev.Set(zoomstr);
	ev.SetSequenceName(GetWindow()->GetParentTabName());
	ev.SetSubTab(GetWindow()->GetParentSubTabName());
	InvokeEvent(ev);
}



void misVolumeSlicer::SetInteractionMode(INTERACTIONMODE mode)
{
	m_pImageStyle->SetInteractionMode(mode);
}

void misVolumeSlicer::ResetContrast()
{
	auto gpu2DRep = dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation);
	if (!gpu2DRep)
		return;
	m_WindowLevelSetting->SetDefaultWindowLevel(
		gpu2DRep->GetImage(gpu2DRep->GetPlaneWithMaximumVisibility())->
		          GetImageDataProperties()->GetViewingProperties().GetInitialLevelWindow());
	m_pImageStyle->SetStateToResetContrast();
}

misMeasurment* misVolumeSlicer::GetMeasurmentService()
{
	return m_MeasurmentService;
}

InteractionState misVolumeSlicer::GetInteractionState() const
{
	return m_pImageStyle->GetInteractionState();
}

void misVolumeSlicer::SetInteractionState(InteractionState val)
{
	m_pImageStyle->SetInteractionState(val);
}

misGeneralToolbarState misVolumeSlicer::GetGeneralToolbarState() const
{
	return m_GeneralToolbarState;
}

void misVolumeSlicer::SetGeneralToolbarState(const misGeneralToolbarState& generalToolbarState)
{
	m_GeneralToolbarState = generalToolbarState;
}

void misVolumeSlicer::ResetViewer()
{
	m_Renderer = m_3DViewer->GetRenderer();
	m_Renderer->RemoveAllViewProps();
	DeleteAllScrews();
	ReleaseImageResource();
}

void misVolumeSlicer::SetAnnotationEnabled(bool showEnable)
{
	m_ShowAnnotation = showEnable;
}

void misVolumeSlicer::SetProstrateState(bool prostrator)
{
	m_ProstrateState = prostrator;
}

void misVolumeSlicer::SetSurgeryType(misApplicationType surgeryType)
{
	m_SurgeryType = surgeryType;
	if (m_SurgeryType == Dental)
		SetShowAnnotationDetail(true);
}

misGeneralToolbarState misVolumeSlicer::ApplyMeasurment(misGeneralToolbarState ls)
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

void misVolumeSlicer::UpdatePanMode()
{
	GetMeasurmentService()->ResetMeasurmentWidget();
	SetControlToPan();
	SetInteractionState(WidgetInteractionState);
	SetGeneralToolbarState(PANSTATE);
	ResetGeneralToolbarState();
}


void misVolumeSlicer::CheckFlyZone(const std::string& segmentationRegion)
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

void misVolumeSlicer::SetRealTimeMode(bool val)
{
	m_RealTimeMode = val;
}

bool misVolumeSlicer::GetRealTimeMode() const
{
	return m_RealTimeMode;
}

std::shared_ptr<ICornerProperties> misVolumeSlicer::GetCornerProperties() const
{
	return m_Cornerproperties;
}

std::shared_ptr<IScrewCompound> misVolumeSlicer::GetScrewWidgetService(misUID uid)
{
	return m_ScrewViewer->GetScrewWidgetService(uid);
}

void misVolumeSlicer::LockAllScrews()
{
	SetAllScrewsLocked(true);
}

void misVolumeSlicer::UnlockAllScrews()
{
	SetAllScrewsLocked(false);
}

void misVolumeSlicer::SetAllScrewsLocked(bool isLocked)
{
	m_ScrewViewer->SetAllScrewsLocked(isLocked);
}


void misVolumeSlicer::RemoveAllScrewServices()
{
	m_ScrewViewer->Clear();
}

vtkRenderer* misVolumeSlicer::GetRenderer()
{
	return m_Renderer;
}

std::shared_ptr<IRepresentation> misVolumeSlicer::GetMainRepresentation()
{
	return m_MainRepresentation;
}



std::shared_ptr<ICursorService> misVolumeSlicer::GetCursorService()
{
	return m_CursorService;
}

void misVolumeSlicer::OnScrew(misUID screwUID)
{
	m_ScrewViewer->OnScrew(screwUID);
}

unsigned long misVolumeSlicer::AddObserver(const itk::EventObject& event, itk::Command* command)
{
	return m_DummyObject->AddObserver(event, command);
}

void misVolumeSlicer::InvokeEvent(const itk::EventObject& event)
{
	m_DummyObject->InvokeEvent(event);
}

bool misVolumeSlicer::HasObserver(const itk::EventObject& event) const
{
	return m_DummyObject->HasObserver(event);
}

void misVolumeSlicer::RemoveRepresentation(std::shared_ptr<IRepresentation> pRepresent)
{
	m_3DViewer->RemoveRepresentation(pRepresent);
	
}

void misVolumeSlicer::AddImageOrientation3DModel(std::shared_ptr<IRepresentation> pRepresentation)
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

std::shared_ptr<Iwindows> misVolumeSlicer::GetWindow() const
{
	return m_3DViewer->GetWindow();
}

double* misVolumeSlicer::GetROICompressData()
{
	vtkPoints* p = m_ROIBox->GetPoints();
	double* compData = m_ROIBox->GetCompressData(p);
	m_ROIBox->UpdateWidgetData();
	return compData;
}

void misVolumeSlicer::DeleteAllScrews()
{
	m_ScrewViewer->DeleteAllScrews();
}

std::shared_ptr<I3DViewer> misVolumeSlicer::Get3DViewer() const
{
	return m_3DViewer;
}



void misVolumeSlicer::GetWidgetBoundingBox(double bounds[6], double extensionScaleFactor)
{
	auto cornerBounds = m_Cornerproperties->GetBounds();
	if (!cornerBounds)
		return;
	double length = cornerBounds[1] - cornerBounds[0];
	double width = cornerBounds[3] - cornerBounds[2];
	double height = cornerBounds[5] - cornerBounds[4];
	delete cornerBounds;

	bounds[0] = -extensionScaleFactor * length;
	bounds[1] = extensionScaleFactor * length;
	bounds[2] = -extensionScaleFactor * width;
	bounds[3] = extensionScaleFactor * width;
	bounds[4] = -extensionScaleFactor * height;
	bounds[5] = extensionScaleFactor * height;
}

void misVolumeSlicer::SetState(int val)
{
	MIS3DInteractionStyle* pStyle = Get3DViewer()->Get3dStyleCamera();
	if (pStyle)
	{
		pStyle->SetState(val);
		GetRenderer()->GetRenderWindow()->GetInteractor()->SetInteractorStyle(pStyle);
	}
}

void misVolumeSlicer::SetWindow(std::shared_ptr<Iwindows> pWindow, int index)
{
	m_IndexInGroup = index;
	m_3DViewer->SetWindow(pWindow, index);
	m_Renderer = pWindow->GetRenderer(index);
}

misViewerTypeDirection misVolumeSlicer::GetTypeDirection() const
{
	return m_ViewerTypeDirection;
 }

IMAGEORIENTATION misVolumeSlicer::GetOrientationDirection() const
{
	TypeDirection typeDirection;
	return  typeDirection.GetOrientationDirection(std::dynamic_pointer_cast<misPlanarRepresentation>(m_MainRepresentation));
 
}

void misVolumeSlicer::SetMainRepresentation(std::shared_ptr<IRepresentation> pMainRep, IMAGEORIENTATION orientation)
{
	m_MainRepresentation = pMainRep;
	InitializeCornerProperties();
	m_CursorService->SetImageOrientation(orientation);
}

void misVolumeSlicer::Reset()
{
	DeleteAllScrews();
	m_3DViewer->Reset();
	if (m_MainRepresentation)
	{
		m_MainRepresentation.reset();
	}
}


void misVolumeSlicer::RemoveRepresentationByName(std::string name)
{
	m_3DViewer->RemoveRepresentationByName(name);
}

void misVolumeSlicer::MakeCurrentRenderer()
{
	m_3DViewer->GetWindow()->GetRenderWindow()->MakeCurrent();
}

void misVolumeSlicer::SetViewPort(const misViewPort& val)
{
	m_ViewPort = val;
	m_3DViewer->SetViewPort(val);
}

void misVolumeSlicer::SetShowManModel(bool val)
{
	m_ShowManModel = val;
}



void misVolumeSlicer::SetDentalSurgeryType(DentalSurgeryType surgeryType)
{
	m_DentalSurgeryType = surgeryType;
	m_Cornerproperties->SetDentalSurgeryType(surgeryType);
}

void misVolumeSlicer::DeleteScrew(misUID screwUID)
{
	m_ScrewViewer->DeleteScrew(screwUID);
}

void misVolumeSlicer::HighlightScrew(misUID screwUID, bool highlight)
{
	m_ScrewViewer->HighlightScrew(screwUID, highlight);
}

void misVolumeSlicer::SetROI(misROI data)
{
	SetROI(data.getData());
}

void misVolumeSlicer::ROIWidgetActivation(bool activation)
{
	if (activation)
	{
		SetROIActive();
		m_ROIBox->On();
	}
	else
		m_ROIBox->Off();
}

void misVolumeSlicer::SetDentalSpecialViewsEnable(bool enabled)
{
	m_DentalSpecialViewEnable = enabled;
}

void misVolumeSlicer::SetPanoramicCoordinateConverter(
	std::shared_ptr<const IPanoramicCoordinatesConverter> coordinateConverter)
{
	m_Cornerproperties->SetPanoramicCoordinateConverter(coordinateConverter);
}

void misVolumeSlicer::InitializeScrewWidget(misScrewWidgetData initVals, IMAGEORIENTATION orientation)
{
	m_ScrewViewer->InitializeScrewWidget(initVals, orientation);
}



void misVolumeSlicer::OffScrew(misUID screwUID)
{
	m_ScrewViewer->OffScrew(screwUID);
}

void misVolumeSlicer::SetToolPosition(double xCoord, double yCoord, double zCoord)
{
}

bool misVolumeSlicer::HasRepresentationByName(const std::string& name)
{
	return !(FindRepresentationByName(name).empty());
}

std::vector<std::shared_ptr<IRepresentation>> misVolumeSlicer::FindRepresentationByName(const std::string& name)
{
	return m_3DViewer->FindRepresentationByName(name);
}

void misVolumeSlicer::SetToolTransform(std::shared_ptr<ITransform> transform)
{
	auto trans = misMathUtils::CreateVtkTransform(transform);
	m_Cornerproperties->SetMatrix(trans->GetMatrix());
	if (m_CursorService)
	{
		m_CursorService->UpdateWidgetPosition();
	}
}

void misVolumeSlicer::AddCoordinateSytemRenderer(std::shared_ptr<ICoordinateSystemRenderer> coordianteRenderer)
{
	m_3DViewer->AddCoordinateSytemRenderer(coordianteRenderer);
}
