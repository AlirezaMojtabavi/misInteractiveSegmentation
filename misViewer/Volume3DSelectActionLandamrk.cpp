#include "stdafx.h"
#include "Volume3DSelectActionLandamrk.h"


 

vtkStandardNewMacro(Volume3DSelectActionLandamrk);

Volume3DSelectActionLandamrk::Volume3DSelectActionLandamrk() : m_LastMouseEventX(0),
m_LastMouseEventY(0)
{
}


void Volume3DSelectActionLandamrk::Create(std::shared_ptr<ILandmarkViewer> landmarkViewer, std::shared_ptr<I3DViewer> viewer,
	std::shared_ptr<ICursorService> cursorService,
	std::shared_ptr<ICornerProperties> cornerProperties,
	::itk::SmartPointer<misVolumeRendererContainer::Self> dummyObject,
	std::shared_ptr<LandmarkDataAndType> landmarkData)
{
	m_3DViewer = viewer;
	m_DummyObject = dummyObject;
	m_Cornerproperties = cornerProperties;
	m_ConvertMouseXYToWorldCoordinate = std::make_unique<ConvertMousexyToWorldCoordinate>(m_Cornerproperties);
	m_LandmarkData = landmarkData;
	m_landamrKviewer = landmarkViewer;
	m_CursorService = cursorService;
}


void Volume3DSelectActionLandamrk::Execute(class vtkObject* caller, unsigned long eventId, void* callData)
{
	if (!m_LandmarkData->m_CaptureLandmark)
	{
		return;
	}
	auto* interactor = reinterpret_cast<vtkRenderWindowInteractor*>(caller);
	int x;
	int y;
	interactor->GetEventPosition(x, y);

	double position[3];
	auto* pStyle = dynamic_cast<MIS3DInteractionStyle*>(interactor->GetInteractorStyle());
	if (!pStyle)
		return;
	auto picker = dynamic_cast<vtkPicker*>(pStyle->GetPointPicker());
	if (!picker)
		return;
	picker->Pick(x, y, 0, m_3DViewer.lock()->GetRenderer());
	vtkPoints* pos = vtkPoints::New();
	pos = picker->GetPickedPositions();
	const auto num = pos->GetNumberOfPoints();
	if (num == 1)
		pos->GetPoint(0, position);
	else
		return;

	if ((0 == position[0]) && (0 == position[1]) && (0 == position[2]))
	{
		return;
	}
	UpdateImageWithSelectedPoint(position);
	
}

void Volume3DSelectActionLandamrk::CaptureLandmark(const double* position)
{
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

}

void Volume3DSelectActionLandamrk::UpdateImageWithSelectedPoint(const double* position)
{
 
	m_Cornerproperties->SetCurrentPosition(position);
	misUpdatePositionEvent ev;
	misUpdatePositionInfoStruct updateStr;
	updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
	updateStr.IsCameraUpdate = true;
	ev.Set(updateStr);
	m_DummyObject->InvokeEvent(ev);
	m_CursorService->UpdateWidgetPosition();
	m_Cornerproperties->SetCurrentPosition(position);
	bool isCameraUpdate = false;
	if (m_LandmarkData && m_LandmarkData->m_CaptureLandmark)
	{
		CaptureLandmark(position);
	}
}



