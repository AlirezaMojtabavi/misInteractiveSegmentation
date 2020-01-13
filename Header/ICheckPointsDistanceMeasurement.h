#pragma once

#include "misGuiStructures.h"
#include "Point.h"

class ICheckPointsDistanceMeasurement
{
public:
	virtual ~ICheckPointsDistanceMeasurement()
	{
	}

	virtual void Reset() = 0;
	virtual int GetNumberOfActiveLandmark() = 0;
	virtual void CheckPointsActivationOn() = 0;
	virtual void CheckPointsActivationOff() = 0;
	virtual LandmarkStateListTypdef GetCheckPointsState() = 0;
	virtual void AdvancedCheckPointsState(int buttonNumbe) = 0;
	virtual misNearsetLandmarkStr UpdateDistanceInformationToCheckPoints(parcast::PointD3 position) = 0;
	virtual bool IsCurrentCheckPointPositionChanged(parcast::PointD3 position) = 0;
	virtual void SetCurrentCheckPointPosition(parcast::PointD3 position) = 0;
	virtual bool AreDistanceToCheckPointsActive() = 0;
	virtual std::vector<itk::Point<double, 3>> GetDiatanceChekPoints()= 0;
};
