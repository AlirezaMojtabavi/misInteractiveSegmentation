#include "stdafx.h"
#include "SlicerPointSelectActionLandamrk.h"

vtkStandardNewMacro(SlicerPointSelectActionLandamrk);

SlicerPointSelectActionLandamrk::SlicerPointSelectActionLandamrk() : m_LastMouseEventX(0),
m_LastMouseEventY(0)
{
}


void SlicerPointSelectActionLandamrk::Create(std::shared_ptr<ILandmarkViewer> landmarkViewer, std::shared_ptr<I3DViewer> viewer,
	std::shared_ptr<ICornerProperties> cornerProperties,
	::itk::SmartPointer<misVolumeRendererContainer::Self> dummyObject,
	std::shared_ptr<ICursorService> currentService,
	std::shared_ptr<LandmarkDataAndType> landmarkData)
{
	m_3DViewer = viewer;
	m_DummyObject = dummyObject;
	m_Cornerproperties = cornerProperties;
	m_CursorService = currentService;
	m_ConvertMouseXYToWorldCoordinate = std::make_unique<ConvertMousexyToWorldCoordinate>(m_Cornerproperties);
	m_LandmarkData = landmarkData;
	m_landamrKviewer = landmarkViewer;

}


void SlicerPointSelectActionLandamrk::Execute(class vtkObject* caller, unsigned long eventId, void* callData)
{
	m_ConvertMouseXYToWorldCoordinate->SetViewer(m_3DViewer.lock());
	UpdateImageWithSelectedPoint();
}

void SlicerPointSelectActionLandamrk::CaptureLandmark(const double* position)
{
	if (!m_LandmarkData->m_CaptureLandmark)
	{
		return;
	}

	unsigned int currentIndex;

	auto currentLandmarkIndex = m_LandmarkData->GetCurrentLandmarkIndex();
	if (!currentLandmarkIndex.is_initialized())
	{
		currentIndex = m_landamrKviewer.lock()->AddNextLandmark(position, m_LandmarkData->m_CurrentLandmarkType, m_LandmarkData->m_CurrentLandmarkLableType);
	}
	else
	{
		currentIndex = currentLandmarkIndex.get();
		m_landamrKviewer.lock()->AddLandmark(currentIndex, position, m_LandmarkData->m_CurrentLandmarkType, m_LandmarkData->m_CurrentLandmarkLableType);
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
	m_LandmarkData->ResetLandmarkIndex();
	m_LandmarkData->m_CaptureLandmark = false;
	m_CursorService->Set3DInteractionCapturedFlag(true);
}

void SlicerPointSelectActionLandamrk::UpdateImageWithSelectedPoint()
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
	if (m_LandmarkData && m_LandmarkData->m_CaptureLandmark)
	{
		CaptureLandmark(position.Elements());
	}
}



