#include "stdafx.h"
#include "..\Header\SlicerPointSelectAction.h"
#include "misInteractorStyleImageExtend.h"

vtkStandardNewMacro(SlicerPointSelectAction);

SlicerPointSelectAction::SlicerPointSelectAction() : m_LastMouseEventX(0),
m_LastMouseEventY(0),
m_GeneralToolbarState()
{
}

SlicerPointSelectAction::~SlicerPointSelectAction()
{
}

 
void SlicerPointSelectAction::Create(std::shared_ptr<I3DViewer> viewer, std::weak_ptr<IVolumeSlicer> slicer,
	std::shared_ptr<ICornerProperties> cornerProperties,
	vtkSmartPointer<misInteractorSTyleImageExtend> interactorStyleImageExtend,
	std::shared_ptr<IBackToPanMode> backToPanMode,
	::itk::SmartPointer<misVolumeRendererContainer::Self> dummyObject,
	std::shared_ptr<ICursorService> currentService, std::shared_ptr<misCameraInteraction> cameraInteraction)
{
	m_3DViewer = viewer;
	m_Slicer = slicer,
		m_pImageStyle = interactorStyleImageExtend;
	m_backToPanMode = backToPanMode;
	m_DummyObject = dummyObject;
	m_Cornerproperties = cornerProperties;
	m_CursorService = currentService;
	m_CameraService = cameraInteraction;
	m_ConvertMouseXYToWorldCoordinate = std::make_unique<ConvertMousexyToWorldCoordinate>(m_Cornerproperties);
 
}


void SlicerPointSelectAction::Execute(class vtkObject* caller, unsigned long eventId, void* callData)
{

	if (!m_Slicer.lock()->GetMainRepresentation() || !m_Slicer.lock()->GetCameraService()->GetCamera() || !m_Slicer.lock()->GetCornerProperties()->GetTransform())
		return;
	m_MainRepresentation = m_Slicer.lock()->GetMainRepresentation();
	m_ConvertMouseXYToWorldCoordinate->SetViewer(m_3DViewer.lock());
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

 
void SlicerPointSelectAction::UpdateImage(bool updateCamera)
{
	auto pos = m_Cornerproperties->GetCurrentPosition();
	if (updateCamera)
		m_Cornerproperties->ResetSightLineIntersectionPoint();
	m_CursorService->UpdateWidgetPosition();
}


void SlicerPointSelectAction::UpdateImageWithSelectedPoint()
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
	UpdateImage(isCameraUpdate);
}



void SlicerPointSelectAction::BackToPanMode()
{
	m_backToPanMode->Update();
}

