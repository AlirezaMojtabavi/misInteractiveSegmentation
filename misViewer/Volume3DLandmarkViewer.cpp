#include "stdafx.h"
#include "Volume3DLandmarkViewer.h"
#include "misCamera.h"
#include "misLandmarkVisualizer.h"
#include "misLandmarkPointerRepresentation.h"
#include "misApplicationSetting.h"
#include "misDistributionEvent.h"


parcast::Volume3DLandmarkViewer::Volume3DLandmarkViewer(std::shared_ptr<I3DViewer> viewer, std::shared_ptr<LandmarkDataAndType> landmarkData,
	std::shared_ptr<ICornerProperties> cornerProperties,
	std::shared_ptr<ICursorService> cursorService,
	std::shared_ptr<IUpdateLandmarkCameraView> updateLandmarkCameraViewer,
	double differenceForViewingSeed, misVolumeRendererContainer::Pointer dummy): LandmarkViewer(viewer, landmarkData, cornerProperties, cursorService,
	                                                 updateLandmarkCameraViewer, differenceForViewingSeed,
	                                                 misViewerTypeDirection::Viewer3DLandmark, dummy)
{
	m_landMarkList.resize(m_maxLandmarkElementSize);
	std::generate(m_landMarkList.begin(), m_landMarkList.end(), []()
		{
			auto appType = misApplicationSetting::GetInstance()->m_WorkflowButtonSet;
			auto radius = 5.5;
			if (appType == Spine)
				radius = 2.0;
			return std::make_shared<misLandmarkPointerRepresentation>(radius, true);
		});
	m_SettingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();
}


parcast::Volume3DLandmarkViewer::~Volume3DLandmarkViewer()
{
}

void Volume3DLandmarkViewer::Render()
{
}

int parcast::Volume3DLandmarkViewer::AddNextLandmark(const double position[3], misLandmarkType category,
	LANDMARKLABLETYPE lableType)
{
	misCamera camera(m_3DViewer->GetRenderer()->GetActiveCamera()->GetPosition(),
		m_3DViewer->GetRenderer()->GetActiveCamera()->GetFocalPoint(),
		m_3DViewer->GetRenderer()->GetActiveCamera()->GetViewUp());
	auto appType = misApplicationSetting::GetInstance()->m_WorkflowButtonSet;
	auto radius = 5.5;
	if (appType == Spine)
		radius = 2.0;
	const parcast::Point<double, 3> point(position);
		misLandmarkVisualizer landmarkVisualizer(
		GetBoundingBox(), camera, m_landMarkList, category,
		lableType, m_ShowLabels, point,
		misViewerTypeDirection::Viewer3DLandmark, 5.5);
	m_3DViewer->AddRepresentation(landmarkVisualizer.GetRepresenTation());
	return landmarkVisualizer.GetIndex();
}

void Volume3DLandmarkViewer::AddLandamrk(const misLandmarkInfoStruct& landmark)
{
	LandmarkViewer::AddLandamrk(landmark);
}

void parcast::Volume3DLandmarkViewer::SetCaptureLandmarkFlag(bool val)
{
	m_LandmarkData->m_CaptureLandmark = val;
}

void parcast::Volume3DLandmarkViewer::AddOrSetNextLandmark(int index, const double position[3], misLandmarkType category,
	LANDMARKLABLETYPE lableType)
{
	auto pLnd = std::make_shared<misLandmarkPointerRepresentation>(index + 1, NORMAL, category, position, lableType,
		5.5, true);
	pLnd->Validate();
	pLnd->SetVisibilityOn();

	const auto handleLength = m_SettingContainer->GetDouble("RegisterationSetting/LandmarkLableHandleLength");
	const auto offsetAngle = m_SettingContainer->GetDouble("RegisterationSetting/LandmarkLableAngleOffset");
	auto lablePosition = GetLablePosition(position, GetBoundingBox(), handleLength, offsetAngle);
	pLnd->SetLabelPosition(lablePosition.Elements());
	m_3DViewer->AddRepresentation(pLnd->GetSurface());
	m_landMarkList[index] = pLnd;
}
void parcast::Volume3DLandmarkViewer::SetLandmarkPosition(int index, const double position[3])
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
					m_landMarkList[i]->Validate();
					SetViewCentrePosition(position);

					misUpdateLandmarkStatusEvent UpdateEv;
					misLandmarkInfoStruct infoStatus;
					infoStatus.CurrentPosition = position;
					infoStatus.landmarkIndex = index;
					infoStatus.Landmarktype = m_LandmarkData->m_CurrentLandmarkType;
					UpdateEv.Set(infoStatus);
					m_DummyObject->InvokeEvent(UpdateEv);

				}
				else
				{
					m_landMarkList[i]->UpdateNormal();
				}
			}
		}
	}
}

void Volume3DLandmarkViewer::SetViewCentrePosition(const double position[3])
{
	if (!position)
	{
		return;
	}
	m_Cornerproperties->SetCurrentPosition(position);
	if (m_CursorService)
		m_CursorService->UpdateWidgetPosition();
	misUpdatePositionEvent ev;
	misUpdatePositionInfoStruct updateStr;
	updateStr.CornerTransform->DeepCopy(m_Cornerproperties->GetTransform());
	updateStr.IsCameraUpdate = true;
	ev.Set(updateStr);
	m_DummyObject->InvokeEvent(ev);
}
