#include "stdafx.h"
#include "..\Header\LandmarkViewer.h"
#include "misLandmarkPointerRepresentation.h"
#include "misLandamrkListCategorizer.h"
#include "misLandmarkVisualizer.h"
#include <misApplicationSetting.h>
#include "LandmarkVisibilty.h"
#include "misDistributionEvent.h"
#include "misSeedBoundingCalculator.h"


parcast::LandmarkViewer::LandmarkViewer(std::shared_ptr<I3DViewer> viewer,
	std::shared_ptr<LandmarkDataAndType> landmarkData,
	std::shared_ptr<ICornerProperties> cornerProperties,
	std::shared_ptr<ICursorService> cursorService,
	std::shared_ptr<IUpdateLandmarkCameraView> updateLandmarkCameraViewer,
	double differenceForViewingSeed, misViewerTypeDirection typeDirection, misVolumeRendererContainer::Pointer dummy)
	: m_LandmarkData(landmarkData),
	m_CursorService(cursorService),
	m_UpdateLandmark(false),
	m_3DViewer(viewer),
	m_Cornerproperties(cornerProperties),
	m_ViewerTypeDirection(typeDirection),
	m_UpdateLandmarkCameraViewer(updateLandmarkCameraViewer),
m_DummyObject(dummy)

{

}


bool LandmarkViewer::ProcessRequest(const itk::EventObject* event)
{
	if ((typeid(*event) == typeid(misAddLandmarkEvent)))
	{
		const misAddLandmarkEvent* pEventData = dynamic_cast<const misAddLandmarkEvent*>(event);
		misLandmarkInfoStruct lndmarkStr = pEventData->Get();
		AddLandamrk(lndmarkStr);

		return true;
	}

	else if ((typeid(*event) == typeid(misUpdateLandmarkStatusEvent)))
	{
		const misUpdateLandmarkStatusEvent* pEventData = dynamic_cast<const misUpdateLandmarkStatusEvent*>(event);
		misLandmarkInfoStruct lndmarkStr = pEventData->Get();

		double* position = new double[3];
		position[0] = lndmarkStr.CurrentPosition[0];
		position[1] = lndmarkStr.CurrentPosition[1];
		position[2] = lndmarkStr.CurrentPosition[2];
		SetLandmarkPosition(lndmarkStr.landmarkIndex, position);
		return true;
	}
	return false;
}

void parcast::LandmarkViewer::SetCurrentLandmarkType(misLandmarkType val)
{
	m_LandmarkData->m_CurrentLandmarkType = val;
	if (m_LandmarkData->GetCurrentLandmarkIndex().is_initialized() && m_LandmarkData->GetCurrentLandmarkIndex().get() >=
		0 &&
		val != UnkownLandmarkType)
		m_landMarkList[m_LandmarkData->GetCurrentLandmarkIndex().get()]->SetCategory(val);
}

void parcast::LandmarkViewer::HideLandmarks()
{
	for (auto& i : m_landMarkList)
	{
		if (i->IsValid())
		{
			i->SetVisibilityOff();
		}
	}
}

int parcast::LandmarkViewer::AddOrSetNextLandmark(const double position[3], misLandmarkType category,
                                                  const LANDMARKLABLETYPE lableType)
{
	int index = -1;
	for (int i = 0; i < m_landMarkList.size(); i++)
	{
		if (!(m_landMarkList[i]->IsValid()))
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		index = static_cast<int>(m_landMarkList.size());
		auto emptyPointer = std::make_shared<misLandmarkPointerRepresentation>(5.5, false);
		emptyPointer->InValidate();
		m_landMarkList.push_back(emptyPointer);
	}

	if (m_landMarkList[index]->IsValid())
	{
		SetLandmarkPosition(index, position);
	}
	else
	{
		AddOrSetNextLandmark(index, position, category, lableType);
	}
	return index;
}

void parcast::LandmarkViewer::UpdateLandmarkCameraView(const int index)
{
	if (m_UpdateLandmarkCameraViewer)
		m_UpdateLandmarkCameraViewer->Update(GetBoundingBox(), m_landMarkList[index]);
}

misSimplePointListType parcast::LandmarkViewer::GetLandmarkList(std::shared_ptr<IImage> pImage, misLandmarkType seedType)
{
 	auto imageGeo = std::make_shared<misImageGeoProperties>(pImage->GetRawImageData());
	auto categorizer = std::make_unique<misLandamrkListCategorizer>(imageGeo);
	return categorizer->GetLandamrks(seedType, m_landMarkList);
}




itk::BoundingBox<double, 3, double>::Pointer LandmarkViewer::GetBoundingBox( )const
{
	const auto boundingBox = m_3DViewer->GetBoundingBox();
	itk::Point<double, 3>  ptmin;
	ptmin[0] = boundingBox[0];
	ptmin[1] = boundingBox[2];
	ptmin[2] = boundingBox[4];
	itk::Point<double, 3>  ptmax;
	ptmax[0] = boundingBox[1];
	ptmax[1] = boundingBox[3];
	ptmax[2] = boundingBox[5];
	auto itkBoundingBox = itk::BoundingBox<double, 3, double>::New();
	itkBoundingBox->SetMaximum(ptmax);
	itkBoundingBox->SetMinimum(ptmin);
	return itkBoundingBox;
}

misVolumeRendererContainer::Pointer LandmarkViewer::GetDummySubject()
{
	return m_DummyObject;
}

std::shared_ptr<LandmarkDataAndType> LandmarkViewer::GetLandmarkData() const
{
	return m_LandmarkData;
}

bool LandmarkViewer::HasObserver(const itk::EventObject& event) const
{
 
		return m_DummyObject->HasObserver(event);
 }

unsigned long LandmarkViewer::AddObserver(const itk::EventObject& event, itk::Command* command)
{
	return m_DummyObject->AddObserver(event, command);
}


void parcast::LandmarkViewer::AddLandmark(int index, const double position[3], misLandmarkType category,
                                          LANDMARKLABLETYPE lableType)
{
	if (m_landMarkList[index]->IsValid())
	{
		if (m_landMarkList[index]->GetCategory() == category)
		{
			SetLandmarkPosition(index, position);
			const auto handleLength = m_SettingContainer->GetDouble("RegisterationSetting/LandmarkLableHandleLength");
			const auto offsetAngle = m_SettingContainer->GetDouble("RegisterationSetting/LandmarkLableAngleOffset");
			const auto boundingBox = m_3DViewer->GetBoundingBox();
			itk::Point<double, 3>  ptmin;	
			ptmin[0] = boundingBox[0];
			ptmin[1] = boundingBox[2];
			ptmin[2] = boundingBox[4];
			itk::Point<double, 3>  ptmax;
			ptmax[0] = boundingBox[1];
			ptmax[1] = boundingBox[3];
			ptmax[2] = boundingBox[5];
			auto itkBoundingBox = itk::BoundingBox<double, 3, double>::New();
			itkBoundingBox->SetMaximum(ptmax);
			itkBoundingBox->SetMinimum(ptmin);
			auto lablePosition = GetLablePosition(position, itkBoundingBox, handleLength, offsetAngle);
			m_landMarkList[index]->SetLabelPosition(lablePosition.Elements());
			UpdateLandmarkCameraView(index);
			return;
		}
	}
	AddOrSetNextLandmark(index, position, category, lableType);
}



double* parcast::LandmarkViewer::GetLandmarkPosition(std::shared_ptr<IImage> pImage,int index, misLandmarkType category)
{
	double* pos = 0;
	if ((index >= 0) && (index < m_landMarkList.size()))
	{
		auto seedList = GetLandmarkList(pImage, category);
		if ((index >= 0) && (index < seedList.size()))
		{
			if (seedList[index].validity)
			{
				pos = new double[3];
				pos[0] = seedList[index].data[0];
				pos[1] = seedList[index].data[1];
				pos[2] = seedList[index].data[2];
				return pos;
			}
		}
	}
	return pos;
}

void parcast::LandmarkViewer::InvalidateLandmarks()
{
	for (auto i = 0; i < m_landMarkList.size(); i++)
	{
		RemoveLandmarkRepresentation(i);
		m_landMarkList[i]->InValidate();
	}
}

void parcast::LandmarkViewer::RemoveLandmarkRepresentation(int index)
{
	const auto size = m_landMarkList.size();
	if ((index < size) && (index >= 0))
	{
		const auto prep = m_landMarkList[index];
		RemoveRepresentation(prep->GetSurface());
	}
}

void parcast::LandmarkViewer::ResetLandMarks()
{
	for (const auto& landmark : m_landMarkList)
	{
		if (landmark->IsValid())
		{
			RemoveRepresentation(landmark->GetSurface());
			landmark->SetCategory(UnkownLandmarkType);
		}
	}
}

void parcast::LandmarkViewer::ResetLandMarks(misLandmarkType lndType)
{
	for (const auto& landmark : m_landMarkList)
	{
		if (landmark->IsValid() && landmark->GetCategory() == lndType)
		{
			RemoveRepresentation(landmark->GetSurface());
			landmark->SetCategory(UnkownLandmarkType);
		}
	}
}

void parcast::LandmarkViewer::RemoveRepresentation(std::shared_ptr<IRepresentation> pRepresent)
{
	m_3DViewer->RemoveRepresentation(pRepresent);
	for (const auto& landmark : m_landMarkList)
	{
		if (landmark->GetSurface() == pRepresent)
			landmark->InValidate();
	}
}

void parcast::LandmarkViewer::InvalidateLandmark(int index)
{
	if ((index >= 0) && (index < m_landMarkList.size()) && m_landMarkList[index])
	{
		RemoveLandmarkRepresentation(index);
		m_landMarkList[index]->InValidate();
	}
}

void LandmarkViewer::Reset()
{
	InvalidateLandmarks();
}

void parcast::LandmarkViewer::SetCurrentLandmark(misLandmarkType val, int index)
{
	if (index != -1)
		m_LandmarkData->SetCurrentLandmarkIndex(index);
	SetCurrentLandmarkType(val);
}

void parcast::LandmarkViewer::SetCurrentLandmarkLableType(LANDMARKLABLETYPE val)
{
	m_LandmarkData->m_CurrentLandmarkLableType = val;
}



bool LandmarkViewer::GetCaptureLandmarkFlag() const
{
	return m_LandmarkData->m_CaptureLandmark;
}

void parcast::LandmarkViewer::RemoveLandMarkRepresentations()
{
	for (const auto& landmark : m_landMarkList)
	{
		if (landmark->IsValid())
		{
			RemoveRepresentation(landmark->GetSurface());
		}
	}
}

void parcast::LandmarkViewer::SetCurrentLandmarkIndex(unsigned int val)
{
	m_LandmarkData->m_CaptureLandmark = val;
}
 

void parcast::LandmarkViewer::ResetCurrentLandmarkIndex() const
{
	m_LandmarkData->ResetLandmarkIndex();
}

LandmarkListType parcast::LandmarkViewer::GetLandmarkList()
{
	return m_landMarkList;
}

double* parcast::LandmarkViewer::GetLandmarkPosition(const int index)
{
	if (m_landMarkList[index]->IsValid())
	{
		const auto pos = new double[3];
		m_landMarkList[index]->GetPosition(pos);
		return pos;
	}
	return nullptr;
}

void parcast::LandmarkViewer::AddLandamrk(const misLandmarkInfoStruct& lndmarkStr)
{
	auto position = m_Cornerproperties->GetCurrentPosition();
	AddLandmark(lndmarkStr.landmarkIndex, position.Elements(), lndmarkStr.Landmarktype,
	            lndmarkStr.landmarkLableType);
	m_LandmarkData->m_CaptureLandmark = false;
	m_UpdateLandmark = false;
}

misLandmarkInfoStruct parcast::LandmarkViewer::UpdateCurrentLandmark(double* pos)
{
	if (m_LandmarkData->GetCurrentLandmarkIndex().is_initialized())
	{
		//if (m_UpdateLandmark)
		//{
		SetLandmarkPosition(m_LandmarkData->GetCurrentLandmarkIndex().get(), pos);

		misLandmarkInfoStruct evData;
		evData.CurrentPosition = pos;
		evData.landmarkIndex = m_LandmarkData->GetCurrentLandmarkIndex().get();
		evData.Landmarktype = m_LandmarkData->m_CurrentLandmarkType;
		evData.landmarkLableType = m_LandmarkData->m_CurrentLandmarkLableType;


		return evData;
		m_UpdateLandmark = false;
	}
}

void LandmarkViewer::SetCaptureLandmark(bool val)
{
	m_LandmarkData->m_CaptureLandmark = false;
	m_UpdateLandmark = false;
}

void LandmarkViewer::SetUpdateLandmarkFlag(bool val)
{
	m_UpdateLandmark = val;
}

misLandmarkInfoStruct LandmarkViewer::PickLandmark(double* position)
{
	if (!m_LandmarkData->GetCurrentLandmarkIndex().is_initialized())
	{
		m_LandmarkData->SetCurrentLandmarkIndex(AddNextLandmark(position, m_LandmarkData->m_CurrentLandmarkType,
		                                                        m_LandmarkData->m_CurrentLandmarkLableType));
	}
	else
	{
		AddLandmark(m_LandmarkData->GetCurrentLandmarkIndex().get(), position, m_LandmarkData->m_CurrentLandmarkType,
		            m_LandmarkData->m_CurrentLandmarkLableType);
	}

	m_CursorService->UpdateWidgetPosition();
	m_Cornerproperties->SetCurrentPosition(position);
	misLandmarkInfoStruct lndStr;
	if (m_LandmarkData->GetCurrentLandmarkIndex().is_initialized())
	{
		lndStr.Landmarktype = m_LandmarkData->m_CurrentLandmarkType;
		lndStr.CurrentPosition = position;
		lndStr.landmarkIndex = m_LandmarkData->GetCurrentLandmarkIndex().get();
		lndStr.landmarkLableType = m_LandmarkData->m_CurrentLandmarkLableType;
	}
	m_LandmarkData->m_CurrentLandmarkType = UnkownLandmarkType;
	m_LandmarkData->ResetLandmarkIndex();
	m_LandmarkData->m_CaptureLandmark = false;
	return lndStr;
}

void parcast::LandmarkViewer::ShowLandmarks()
{
	for (auto& landamrk : m_landMarkList)
	{
		if (landamrk->IsValid())
		{
			landamrk->SetVisibilityOn();
		}
	}
}

misLandmarkInfoStruct LandmarkViewer::UpdateLandmarkByWidget(double* pos)
{
	misLandmarkInfoStruct landmarkStr;

	if (m_UpdateLandmark)
	{
		_ASSERT(m_LandmarkData->GetCurrentLandmarkIndex().is_initialized());
		if (!m_LandmarkData->GetCurrentLandmarkIndex().is_initialized())
			return landmarkStr;

		SetLandmarkPosition(m_LandmarkData->GetCurrentLandmarkIndex().get(), pos);
		m_UpdateLandmark = false;

		landmarkStr.CurrentPosition = pos;
		landmarkStr.landmarkIndex = m_LandmarkData->GetCurrentLandmarkIndex().get();
		landmarkStr.Landmarktype = m_LandmarkData->m_CurrentLandmarkType;
		landmarkStr.landmarkLableType = m_LandmarkData->m_CurrentLandmarkLableType;
		m_UpdateLandmark = false;
		return landmarkStr;
	}
}

parcast::PointD3 parcast::LandmarkViewer::GetLablePosition(const double* position,
                                                           const itk::BoundingBox<double, 3, double>::Pointer&
                                                           boundingBox, const double handleLength,
                                                           const double offsetAngle) const
{
	auto lablePositionCalculator = parcast::LandmarkLablePositionCalculator(
		parcast::PointD3(boundingBox->GetMinimum().GetDataPointer()),
		parcast::PointD3(boundingBox->GetMaximum().GetDataPointer()), handleLength, offsetAngle);
	const auto landmarkPos = parcast::PointD3(position[0], position[1], position[2]);
	return lablePositionCalculator.GetLabelPosition(landmarkPos,m_ViewerTypeDirection);
}


misROI LandmarkViewer::GetSeedBounding(std::shared_ptr<IImage> pImage,int* dimenstion, double* spacing)
{
	misSimplePointListType tFGSeedList = GetLandmarkList(pImage, ForeGroundSeed);
	misSeedBoundingCalculator seedCalculator(tFGSeedList);
	return seedCalculator.GetSeedBounding( dimenstion, spacing);
}
