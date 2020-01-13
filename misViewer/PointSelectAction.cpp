#include "stdafx.h"
#include "..\Header\PointSelectAction.h"
#include "misInteractorSTyleImageExtend.h"


PointSelectAction::PointSelectAction(std::shared_ptr<I3DViewer> viewer, std::weak_ptr<IVolumeSlicer> slicer,
                                     std::shared_ptr<ICornerProperties> cornerProperties,
                                     vtkSmartPointer<misInteractorSTyleImageExtend> interactorStyleImageExtend,
                                     std::shared_ptr<IBackToPanMode> backToPanMode,
                                     misVolumeRendererContainer::Pointer dummyObject,
                                     std::shared_ptr<ICursorService> currentService, std::shared_ptr<misCameraInteraction> cameraInteraction, 
	std::shared_ptr<LandmarkDataAndType> landmarkData)
	: m_3DViewer(viewer),
	m_Slicer(slicer),
	m_pImageStyle(interactorStyleImageExtend),
	m_backToPanMode(backToPanMode),
	m_DummyObject(dummyObject),
	m_Cornerproperties(cornerProperties),
	m_CursorService(currentService),
	m_CameraService(cameraInteraction),
	m_ConvertMouseXYToWorldCoordinate(std::make_unique<ConvertMousexyToWorldCoordinate>(m_Cornerproperties, cameraInteraction)),
	m_LandmarkData(landmarkData)

{
}

PointSelectAction::~PointSelectAction()
{
}


void PointSelectAction::Execute(class vtkObject* caller, unsigned long eventId, void* callData)
{
 
	if (!m_Slicer.lock()->GetMainRepresentation() || !m_Slicer.lock()->GetCameraService()->GetCamera() || !m_Slicer.lock()->GetCornerProperties()->GetTransform())
		return;
	m_MainRepresentation = m_Slicer.lock()->GetMainRepresentation();
	m_ConvertMouseXYToWorldCoordinate->SetMainRepresentation(m_MainRepresentation);
	InteractionState state = m_pImageStyle->GetInteractionState();
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
			BackToPanMode();
			misBackToPanModeEvent ev;
			m_DummyObject->InvokeEvent(ev);
			return;
		}
	}
}


void PointSelectAction::CaptureLandmark(const double* position)
{
	unsigned int currentIndex;

	if (!m_LandmarkData->m_currentLandmarkIndex.is_initialized())
	{
		currentIndex = m_Slicer.lock()->AddNextLandmark(position, m_LandmarkData->m_CurrentLandmarkType, m_LandmarkData->m_CurrentLandmarkLableType);
	}
	else
	{
		currentIndex = m_LandmarkData->m_currentLandmarkIndex.get();
		m_Slicer.lock()->AddLandmark(currentIndex, position, m_LandmarkData->m_CurrentLandmarkType, m_LandmarkData->m_CurrentLandmarkLableType);
	}
	if (currentIndex != -1)
	{
		misLandmarkInfoStruct landmarkStr;
		landmarkStr.Landmarktype = m_LandmarkData->m_CurrentLandmarkType;
		landmarkStr.CurrentPosition = position;
		landmarkStr.landmarkIndex = currentIndex;
		landmarkStr.landmarkLableType = m_LandmarkData->m_CurrentLandmarkLableType;
		landmarkStr.validity = true;
		misAddLandmarkEvent landmarkEv;
		landmarkEv.Set(landmarkStr);
		m_DummyObject->InvokeEvent(landmarkEv);
	}

	m_LandmarkData->m_CurrentLandmarkType = UnkownLandmarkType;
	m_LandmarkData->m_currentLandmarkIndex.reset();
	m_LandmarkData->m_CaptureLandmark = false;
	m_CursorService->Set3DInteractionCapturedFlag(true);
}

void PointSelectAction::UpdateImage(bool updateCamera)
{
	auto pos = m_Cornerproperties->GetCurrentPosition();
	if (updateCamera)
		m_Cornerproperties->ResetSightLineIntersectionPoint();
	m_CursorService->UpdateWidgetPosition();
}

 


void PointSelectAction::UpdateImageWithSelectedPoint()
{

	auto interactor = dynamic_cast<vtkRenderWindowInteractor*> (m_3DViewer.lock()->GetWindow()->GetInterActor().GetPointer());
	auto position = m_ConvertMouseXYToWorldCoordinate->CalculateNewPosition(interactor);
 

	m_Cornerproperties->SetCurrentPosition(position.Elements());

	misUpdatePositionEvent ev;
	misUpdatePositionInfoStruct updateStr;
	updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
	updateStr.IsCameraUpdate = true;
	ev.Set(updateStr);
	m_DummyObject->InvokeEvent(ev);

	bool isCameraUpdate = false;
	if (m_LandmarkData->m_CaptureLandmark)
	{
		CaptureLandmark(position.Elements());
		isCameraUpdate = true;
	}
	UpdateImage(isCameraUpdate);
}



void PointSelectAction::BackToPanMode()
{
	m_backToPanMode->Update();
}

