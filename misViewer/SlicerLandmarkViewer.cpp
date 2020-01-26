#include "stdafx.h"
#include "SlicerLandmarkViewer.h"
#include "misCamera.h"
#include "misLandmarkVisualizer.h"
#include "LandmarkVisibilty.h"
#include "misLandmarkPointerRepresentation.h"
#include "misApplicationSetting.h"


parcast::SlicerLandmarkViewer::SlicerLandmarkViewer(std::shared_ptr<I3DViewer> viewer,
                                                    std::shared_ptr<LandmarkDataAndType> landmarkData,
                                                    std::shared_ptr<ICornerProperties> cornerProperties,
                                                    std::shared_ptr<ICursorService> cursorService,
                                                    std::shared_ptr<IUpdateLandmarkCameraView>
                                                    updateLandmarkCameraViewer,
                                                    double differenceForViewingSeed, misViewerTypeDirection typeDirection,  misVolumeRendererContainer::Pointer dummy) : 
	LandmarkViewer(	viewer, landmarkData, cornerProperties, cursorService, updateLandmarkCameraViewer, differenceForViewingSeed,
														typeDirection, dummy),
	m_LandmarkVisibilty(std::make_unique<LandmarkVisibilty>(cornerProperties, differenceForViewingSeed))
{
	m_landMarkList.resize(m_maxLandmarkElementSize);
	std::generate(m_landMarkList.begin(), m_landMarkList.end(), []()
		{
			auto appType = misApplicationSetting::GetInstance()->m_WorkflowButtonSet;
			auto radius = 5.5;
			if (appType == Spine)
				radius = 2.0;
			return std::make_shared<misLandmarkPointerRepresentation>(radius, false);
		});
	m_SettingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();


}


parcast::SlicerLandmarkViewer::~SlicerLandmarkViewer()
{
}
int parcast::SlicerLandmarkViewer::AddNextLandmark(const double position[3], misLandmarkType category,
	LANDMARKLABLETYPE lableType)
{
	misCamera camera(m_3DViewer->GetRenderer()->GetActiveCamera()->GetPosition(),
		m_3DViewer->GetRenderer()->GetActiveCamera()->GetFocalPoint(),
		m_3DViewer->GetRenderer()->GetActiveCamera()->GetViewUp());
	const parcast::Point<double, 3> point(position);
	misLandmarkVisualizer landmarkVisualizer(
		GetBoundingBox(), camera, m_landMarkList, category,
		lableType, m_ShowLabels, point,
		m_ViewerTypeDirection, 5.5);
	m_3DViewer->AddRepresentation(landmarkVisualizer.GetRepresenTation());
	return landmarkVisualizer.GetIndex();
}

void SlicerLandmarkViewer::AddLandamrk(const misLandmarkInfoStruct& landmark)
{
	LandmarkViewer::AddLandamrk(landmark);
	m_LandmarkVisibilty->CheckVisibility(m_landMarkList);
}
void SlicerLandmarkViewer::CheckVisibility() const
{
	m_LandmarkVisibilty->CheckVisibility(m_landMarkList);
}

void SlicerLandmarkViewer::Render()
{
	CheckVisibility();
}
void parcast::SlicerLandmarkViewer::AddOrSetNextLandmark(int index, const double position[3], misLandmarkType category,
	LANDMARKLABLETYPE lableType)
{
	auto pLnd = std::make_shared<misLandmarkPointerRepresentation>(index + 1, NORMAL, category, position, lableType,
		5.5, false);
	pLnd->Validate();
	pLnd->SetVisibilityOn();

	const auto handleLength = m_SettingContainer->GetDouble("RegisterationSetting/LandmarkLableHandleLength");
	const auto offsetAngle = m_SettingContainer->GetDouble("RegisterationSetting/LandmarkLableAngleOffset");
	auto lablePosition = GetLablePosition(position, GetBoundingBox(), handleLength, offsetAngle);
	pLnd->SetLabelPosition(lablePosition.Elements());
	m_3DViewer->AddRepresentation(pLnd->GetSurface());
	m_landMarkList[index] = pLnd;
}
void parcast::SlicerLandmarkViewer::SetLandmarkPosition(int index, const double position[3])
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
					m_landMarkList[i]->SetLabelData(i + 1, SELECTED, m_LandmarkData->m_CurrentLandmarkLableType);
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
void parcast::SlicerLandmarkViewer::SetCaptureLandmarkFlag(bool val)
{
	m_LandmarkData->m_CaptureLandmark = val;
	m_CursorService->Set3DInteractionCapturedFlag(!val);
}