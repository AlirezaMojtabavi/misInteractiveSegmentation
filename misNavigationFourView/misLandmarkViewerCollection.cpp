#include "stdafx.h"
#include "..\Header\misLandmarkViewerCollection.h"
#include "ILandmarkRegistrationCalculator.h"


misLandmarkViewerCollection::misLandmarkViewerCollection(std::shared_ptr<IGroupViewerSetting> groupViewerSetting)
	:m_GroupViewSetting(groupViewerSetting)
{
}
 

void misLandmarkViewerCollection::ImageLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index ,
	LANDMARKLABLETYPE lableType )
{
	auto addNextLandmarkEvent = new misAddLandmarkEvent();
	misDistributionMap* landMarkMap = m_GroupViewSetting->FindDistributionMap(addNextLandmarkEvent);
	if (!landMarkMap)
		return;
	for (auto viewer : m_LandmarkViewerAdapters)
	{
		viewer->ImageLandmarkCaptureEnable(pLandmarkType, index, lableType);
	}
	delete addNextLandmarkEvent;
}


void misLandmarkViewerCollection::ImageLandmarkUpdateEnable(misLandmarkType pLandmarkType, int index /*=-1*/)
{
	misAddLandmarkEvent* addNextLandmarkEvent = new misAddLandmarkEvent();
	misDistributionMap* landMarkMap = m_GroupViewSetting->FindDistributionMap(addNextLandmarkEvent);
	if (!landMarkMap)
		return;
	for (auto viewer : m_LandmarkViewerAdapters)
	{
		viewer->ImageLandmarkUpdateEnable(pLandmarkType, index);
	}
}
void misLandmarkViewerCollection::ImageLandmarkUpdateDisable()
{
	misAddLandmarkEvent* addNextLandmarkEvent = new misAddLandmarkEvent();
	misDistributionMap* landMarkMap = m_GroupViewSetting->FindDistributionMap(addNextLandmarkEvent);
	if (!landMarkMap)
		return;
	for (auto viewer : m_LandmarkViewerAdapters)
	{
		viewer->ImageLandmarkUpdateDisable();
	}
}

void misLandmarkViewerCollection::VolumeLandmarkCaptureEnable(misLandmarkType pLandmarkType, int index /*=-1*/, LANDMARKLABLETYPE lableType /*= NUMERICALLANDMARK*/)
{
	misAddLandmarkEvent* addNextLandmarkEvent = new misAddLandmarkEvent();
	misDistributionMap* landMarkMap = m_GroupViewSetting->FindDistributionMap(addNextLandmarkEvent);
	if (!landMarkMap)
		return;

	for (auto viewer : m_LandmarkViewerAdapters)
	{
		viewer->GetLandmarkViewer()->SetCurrentLandmark(pLandmarkType, index);
		viewer->GetLandmarkViewer()->SetCurrentLandmarkLableType(lableType);
		viewer->GetLandmarkViewer()->SetCaptureLandmarkFlag(true);

	}

}
void misLandmarkViewerCollection::ImageLandmarkCaptureDisable()
{
	for (auto viewer : m_LandmarkViewerAdapters)
	{
		viewer->ImageLandmarkCaptureDisable();
	}
}

void misLandmarkViewerCollection::VolumeLandmarkCaptureDisable()
{
	for (auto viewer : m_LandmarkViewerAdapters)
	{
		viewer->SetCurrentLandmarkType(UnkownLandmarkType);
		viewer->GetLandmarkViewer()->SetCaptureLandmarkFlag(false);
		viewer->GetLandmarkViewer()->ResetCurrentLandmarkIndex();
	}
}

void misLandmarkViewerCollection::Render()
{
	for (auto adapter : m_LandmarkViewerAdapters)
	{
		adapter->GetLandmarkViewer()->Render();
	}
}

void misLandmarkViewerCollection::HandleUpdatePositionEvent(const misUpdatePositionEvent* pEvent)
{
	/*for (auto landmarkViewer : m_LandmarkViewerAdapters)
	{
		auto  evData = landmarkViewer->GetLandmarkViewer()->UpdateCurrentLandmark(toolTipPoint);
		misAddLandmarkEvent ev2;
		ev2.Set(evData);
		InvokeEvent(ev2);
	}*/
}

std::vector<std::shared_ptr<IPackage2DLandmarkAdapter>> misLandmarkViewerCollection::GetLandmarkViewers()
{
	return m_LandmarkViewerAdapters;
}

void misLandmarkViewerCollection::AddAdapter(std::shared_ptr<IPackage2DLandmarkAdapter> adpater)
{
	m_LandmarkViewerAdapters.push_back(adpater);
	AddObservers(adpater->GetLandmarkViewer());
}

std::shared_ptr<IPackage2DLandmarkAdapter> misLandmarkViewerCollection::GetLandmark3DViewer()
{
	return GetLandmarkViewers()[3];
}


void misLandmarkViewerCollection::ResetAllLandMarks()
{
	for (auto packageViewer : m_LandmarkViewerAdapters)
		packageViewer->GetLandmarkViewer()->ResetLandMarks();
}

void misLandmarkViewerCollection::ShowLandmarks()
{
	for (auto viewer : m_LandmarkViewerAdapters)
		viewer->GetLandmarkViewer()->ShowLandmarks();
}

void misLandmarkViewerCollection::HideLandmarks(TypeOfViewer typeOfviewer)
{
	if (typeOfviewer == INavigationViewersNView::ALLVIEWERS)
		for (auto packageViewer : m_LandmarkViewerAdapters)
			packageViewer->GetLandmarkViewer()->HideLandmarks();
	else
		for (auto adapter : m_LandmarkViewerAdapters)
		{
			adapter->GetLandmarkViewer()->HideLandmarks();
		}
}



void misLandmarkViewerCollection::InvalidateLandmark(int index)
{
	for (auto packageViewer : m_LandmarkViewerAdapters)
		packageViewer->GetLandmarkViewer()->InvalidateLandmark(index);
}
void misLandmarkViewerCollection::ResetLandMarks(misLandmarkType lndType)
{
	for (auto packageViwer : m_LandmarkViewerAdapters)
		packageViwer->GetLandmarkViewer()->ResetLandMarks(lndType);
}
void misLandmarkViewerCollection::UpdateLandmarks(misLandmarkInfoStruct &landmarkInfo)
{
	auto viewers = m_LandmarkViewerAdapters;
	for (auto &viewer : viewers)
	{
		if (viewer && landmarkInfo.validity)
			viewer->GetLandmarkViewer()->AddLandmark(landmarkInfo.landmarkIndex, landmarkInfo.CurrentPosition.GetDataPointer(),
				landmarkInfo.Landmarktype, landmarkInfo.landmarkLableType);
	}
}
void misLandmarkViewerCollection::AddLandmark(unsigned int landmarkIndex, itk::Point<double, 3> landmark, misLandmarkType landmarkType,
	LANDMARKLABLETYPE lableType)
{
	for (const auto adapter2D : m_LandmarkViewerAdapters)
	{
		adapter2D->GetLandmarkViewer()->AddLandmark(landmarkIndex, landmark.GetDataPointer(), landmarkType, lableType);
	}

}

void misLandmarkViewerCollection::ReleaseResource()
{
	ResetAllLandMarks();
	ImageLandmarkCaptureDisable();
	ImageLandmarkUpdateDisable();
	VolumeLandmarkCaptureDisable();
}




void misLandmarkViewerCollection::AddObservers(std::shared_ptr<parcast::ILandmarkViewer> viewer)
{
	typedef itk::MemberCommand< misLandmarkViewerCollection >   ObserverType;
	ObserverType::Pointer      addNextLandmarkObserver = ObserverType::New();
	addNextLandmarkObserver->SetCallbackFunction(this, &misLandmarkViewerCollection::DistributeEvent);
	if (!viewer-> HasObserver(misAddLandmarkEvent()))
	{
		viewer->AddObserver(misAddLandmarkEvent(), addNextLandmarkObserver);
	}

	ObserverType::Pointer      updateLandmarkStatusObserver = ObserverType::New();
	updateLandmarkStatusObserver->SetCallbackFunction(this, &misLandmarkViewerCollection::DistributeEvent);
	if (!viewer->HasObserver(misUpdateLandmarkStatusEvent()))
	{
		viewer->AddObserver(misUpdateLandmarkStatusEvent(), updateLandmarkStatusObserver);
	}
}

void misLandmarkViewerCollection::DistributeEvent(itk::Object *caller, const itk::EventObject& pEvent)
{
	size_t callerIndex = 0;
	auto const found = FindDistributerViewer(caller, callerIndex);
		if (!found)
			return;
	if (typeid(pEvent) == typeid(misUpdatePositionEvent))
	{

		HandleUpdatePositionEvent(dynamic_cast<const misUpdatePositionEvent*>(&pEvent));
	}
	auto targetMap = m_GroupViewSetting->FindDistributionMap(&pEvent);
	for (int i = 0; i < m_LandmarkViewerAdapters.size(); i++)
	{
		auto viewer = m_LandmarkViewerAdapters[i]->GetLandmarkViewer();
		if (viewer && targetMap->GetMap()[callerIndex][i])
				viewer->ProcessRequest(&pEvent);
	}
	if (m_ExternalEventViewer)
		m_ExternalEventViewer(caller, pEvent);
	m_DummyObject->InvokeEvent(pEvent);
}

bool misLandmarkViewerCollection::HasObserver(const itk::EventObject& event) const
{
	return m_DummyObject->HasObserver(event);
}

unsigned long misLandmarkViewerCollection::AddObserver(const itk::EventObject& event, itk::Command* command)
{
	return m_DummyObject->AddObserver(event, command);
}

void misLandmarkViewerCollection::InvokeEvent(const itk::EventObject& event)
{
	m_DummyObject->InvokeEvent(event);
}
 
inline void misLandmarkViewerCollection::SetExternalEventViewer(
	std::function<void(itk::Object* caller, const itk::EventObject& pEvent)> val)
{
	m_ExternalEventViewer = val;
}

bool misLandmarkViewerCollection::FindDistributerViewer(itk::Object* caller, size_t& viewerIndex)
{
	auto containerRepresnetation = dynamic_cast<misRepresentationContainer*>(caller);
	auto containerViewer = dynamic_cast<misVolumeRendererContainer*>(caller);

	std::shared_ptr<IRepresentation> callerRepresentation;
	IVolumeRenderer* callerViewer = nullptr;

	if (containerRepresnetation)
		callerRepresentation = containerRepresnetation->GetRepresenation();
	if (containerViewer)
		callerViewer = containerViewer->GetViewer();

	if ((callerRepresentation) || (callerViewer))
	{
		for (int i = 0; i < m_LandmarkViewerAdapters.size(); i++)
		{
			auto viewer = m_LandmarkViewerAdapters[i]->GetLandmarkViewer()->GetDummySubject()->GetViewer();
			if (viewer)
			{
				const bool imageMatch = viewer == callerViewer;
				bool repMatch = false;
				auto currentRep = std::dynamic_pointer_cast<IRepresentation>(viewer->GetMainRepresentation());
				if (currentRep)
					repMatch = currentRep == callerRepresentation;
				if (repMatch || imageMatch)
				{
					viewerIndex = i;
					return true;
				}
			}
		}
	}
	return false;
}
