#include "stdafx.h"
#include "..\Header\BackToPanMode.h"



BackToPanMode::BackToPanMode(misMeasurment::Pointer measurment, vtkSmartPointer<misInteractorSTyleImageExtend> interactorSTyleImageExtend,
	std::shared_ptr<I3DViewer> viewer, misVolumeRendererContainer::Pointer dummyObject)
	:m_MeasurmentService(measurment),
	m_pImageStyle(interactorSTyleImageExtend),
	m_3DViewer(viewer),
	m_DummyObject(dummyObject)
{
	UpdateImageInteractionState();
}
void BackToPanMode::SetControlToPan()
{
	m_pImageStyle->SetSatateToRender();
}



void BackToPanMode::Update()
{
	UpdateImageInteractionState();
	SetControlToPan();
	ResetGeneralToolbarInRightClick();
}

void BackToPanMode::UpdateImageInteractionState()
{
	m_GeneralToolbarState = PANSTATE;
	m_MeasurmentService->ResetMeasurmentWidget();
}

void BackToPanMode::ResetGeneralToolbarState() const
{
	misChangeButtomStateCore ev;
	ev.Set(PANSTATE);
	ev.SetSequenceName(m_3DViewer->GetWindow()->GetParentTabName());
	ev.SetSubTab(m_3DViewer->GetWindow()->GetParentSubTabName());
	m_DummyObject->InvokeEvent(ev);
}

void BackToPanMode::ResetGeneralToolbarInRightClick()
{
	misAutoMeasurment* tempMeasurment = dynamic_cast<misAutoMeasurment *>(m_MeasurmentService.GetPointer());
	if (NULL != tempMeasurment)
	{
		misResetAutoMeasurmentButtomCore ev2;
		ev2.SetSequenceName(m_3DViewer->GetWindow()->GetParentTabName());
		ev2.SetSubTab(m_3DViewer->GetWindow()->GetParentSubTabName());
		m_DummyObject->InvokeEvent(ev2);
	}

	ResetGeneralToolbarState();
}
