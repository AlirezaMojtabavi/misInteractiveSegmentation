#pragma once
#include "misCalculateLandmarkDistance.h"
#include "ICheckPointsDistanceMeasurement.h"

class misCheckPointsDistanceMeasurement : public ICheckPointsDistanceMeasurement
{
public:
	void Reset() override;
	int GetNumberOfActiveLandmark() override;
	void CheckPointsActivationOn() override;
	void CheckPointsActivationOff() override;
	LandmarkStateListTypdef GetCheckPointsState() override;
	void AdvancedCheckPointsState(int buttonNumbe) override;
	misNearsetLandmarkStr UpdateDistanceInformationToCheckPoints(parcast::PointD3 position) override;
	bool IsCurrentCheckPointPositionChanged(parcast::PointD3) override;
	void SetCurrentCheckPointPosition(parcast::PointD3) override;
	bool AreDistanceToCheckPointsActive() override;
	std::vector<itk::Point<double, 3>> GetDiatanceChekPoints() override;
private:
	misCalculateLandmarkDistance m_DistanceToCheckPoints;
	misNearsetLandmarkStr m_lastPointerDistanceInfo;

};
