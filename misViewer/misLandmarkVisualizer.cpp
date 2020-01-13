#include "stdafx.h"

#include "misCamera.h"
#include "misLandmarkPointerRepresentation.h"
#include "misLandmarkVisualizer.h"
#include "misLandmarkenums.h"
#include "LandmarkLablePositionCalculator.h"
#include "misApplicationSetting.h"

misLandmarkVisualizer::misLandmarkVisualizer(itk::BoundingBox<double, 3, double>::Pointer bounding, misCamera camera,
	LandmarkListType& landMarkList, misLandmarkType category,
	LANDMARKLABLETYPE lableType, bool showLabel, parcast::Point<double, 3> position,
	misViewerTypeDirection const& viewerDirection, double labelRadius)
	: m_BoundingBox(bounding),
	m_Camera(camera),
	m_landMarkList(landMarkList),
	m_Category(category),
	m_LableType(lableType),
	m_ShowLabel(showLabel),
	m_Position(position),
	m_ViewerDirection(viewerDirection)
{
	const auto settingContainer = misApplicationSetting::GetInstance()->GetSettingsContainer();
	const auto offsetAngle = settingContainer->GetDouble("RegisterationSetting/LandmarkLableAngleOffset");
	m_LandmarkPositionCalculator = std::make_unique<parcast::LandmarkLablePositionCalculator>(
		parcast::PointD3(m_BoundingBox->GetMinimum().GetDataPointer()),
		parcast::PointD3(m_BoundingBox->GetMaximum().GetDataPointer()), 30, offsetAngle);
	CreateRepresentation(labelRadius);

}

void misLandmarkVisualizer::CreateRepresentation(double labelRadius)
{
	int HitCounter = 0;
	CalculateIndexes(m_Index, HitCounter);
	if (m_Index == -1)
	{
		m_Index = static_cast<int> (m_landMarkList.size());
		auto emptyPointer = std::make_shared<misLandmarkPointerRepresentation>(labelRadius, true);
		emptyPointer->InValidate();
		m_landMarkList.push_back(emptyPointer);
		HitCounter = m_Index;
	}
	m_Representation = std::make_shared<misLandmarkPointerRepresentation>(m_Index + 1, SELECTED,
		m_Category, m_Position.Elements(), m_LableType, labelRadius, true);


	auto lablePoint = m_LandmarkPositionCalculator->GetLabelPosition(
		parcast::PointD3(m_Position.Elements()), m_ViewerDirection);

	if(m_ShowLabel)
		m_Representation->SetLabelPosition(lablePoint[0], lablePoint[1], lablePoint[2]);
	m_Representation->Validate();
	m_Representation->SetVisibilityOn();
	m_landMarkList[m_Index] = m_Representation;

}

void misLandmarkVisualizer::CalculateIndexes(int &index, int &HitCounter)
{
	for (int i = 0; i < m_landMarkList.size(); i++)
	{
		if (((m_landMarkList[i]->GetCategory() == m_Category) || (m_landMarkList[i]->GetCategory() == UnkownLandmarkType))
			&& (m_landMarkList[i]->IsValid() == false))
		{
			index = i;
			break;
		}
	}
	for (int i = 0; i < m_landMarkList.size(); i++)
	{
		if (m_landMarkList[i]->GetCategory() == m_Category)
		{
			HitCounter++;
		}
	}
}

std::shared_ptr<IRepresentation> misLandmarkVisualizer::GetRepresenTation()
{
	return m_Representation->GetSurface();
}

int misLandmarkVisualizer::GetIndex() const
{
	return m_Index;
}
