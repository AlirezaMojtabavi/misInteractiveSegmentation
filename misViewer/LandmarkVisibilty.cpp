#include "stdafx.h"
#include "..\Header\LandmarkVisibilty.h"


LandmarkVisibilty::LandmarkVisibilty(std::shared_ptr<ICornerProperties> corenrProp, double differenceForViewingSeed)
	:m_Cornerproperties(corenrProp), m_DifferenceForViewingSeed(differenceForViewingSeed)
{
}


void LandmarkVisibilty::CheckVisibility(const LandmarkListType& landMarkList) const
{
	auto currentPos = m_Cornerproperties->GetCurrentPosition();
	misSimplePointType  currentPosition;
	currentPosition.SetPoint(currentPos.Elements());

	auto  dif = 0.0f;

	for (auto landmark : landMarkList)
	{
		if (!(landmark) || (!landmark->IsValid()))
			continue;
		 misSimplePointType  landMarkPositionPoint;
		double landmarkPos[3];
		landmark->GetPosition(landmarkPos);
		landMarkPositionPoint.SetPoint(landmarkPos);
		misSimplePointType planeNormal = m_Cornerproperties->GetPlaneNormal();

		landMarkPositionPoint.Multiply(planeNormal);
		planeNormal.Multiply(currentPosition);
		dif = static_cast<float> (misSimplePointType::EuclideanDistance(landMarkPositionPoint, planeNormal));

		if (dif < m_DifferenceForViewingSeed)
		{
			if (landmark->IsValid())
			{
				landmark->SetVisibilityOn();
				landmark->UpdateAsSelected();
			}
		}
		else
		{
			if (landmark->IsValid())
			{
				landmark->SetVisibilityOff();
			}
		}
	}

}
