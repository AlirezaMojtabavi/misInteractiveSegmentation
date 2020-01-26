#include "stdafx.h"
#include "Volume2DPointSelectAction.h"
#include "MIS3DInteractionStyle.h"
#include "misDistributionEvent.h"
#include "misColorPointWidget.h"

vtkStandardNewMacro(Volume2DPointSelectAction);

void Volume2DPointSelectAction::Create(std::shared_ptr<LandmarkDataAndType> landmarkdata, std::shared_ptr<ILandmarkViewer> landamrkViewer, misVolumeRendererContainer::Pointer subject)
{
	m_LandmarkData = landmarkdata;
	m_LandmarkViewer = landamrkViewer;
	m_DummySubject = subject;
}

void Volume2DPointSelectAction::Execute(vtkObject* caller, unsigned long eventId, void* callData)
{
	misColorPointWidget* pointWidget = dynamic_cast<misColorPointWidget*>(caller);
	if (pointWidget)
	{
		double pos[3];
		pointWidget->GetPosition(pos);
		if (m_LandmarkData->GetCurrentLandmarkIndex().is_initialized())
		{
			//if (m_UpdateLandmark)
			//{
			m_LandmarkViewer->SetLandmarkPosition(m_LandmarkData->GetCurrentLandmarkIndex().get(), pos);

			misLandmarkInfoStruct evData;
			evData.CurrentPosition = pos;
			evData.landmarkIndex = m_LandmarkData->GetCurrentLandmarkIndex().get();
			evData.Landmarktype = m_LandmarkData->m_CurrentLandmarkType;
			evData.landmarkLableType = m_LandmarkData->m_CurrentLandmarkLableType;

			misAddLandmarkEvent ev;
			ev.Set(evData);
			m_DummySubject->InvokeEvent(ev);
 
		}
	}
}

 