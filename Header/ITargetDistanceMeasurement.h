#pragma once
#include "Point.h"

class ITargetDistanceMeasurement
{
public:
	virtual ~ITargetDistanceMeasurement()
	{
	}

	virtual void Reset() = 0;
	virtual void AdvancedTargetPointState(int state) = 0;
	virtual itk::Point<double, 3> GetTargetPointPosition(int index) = 0;
	virtual bool IsTargetPointActive() = 0;
	virtual void TargetPointActivationOn() =0;
	virtual void TargetPointActivationOff() = 0;
	virtual parcast::Vector<double> GetVectorToTargetPoint(const double* realPosition) const = 0;
	virtual void SetTargetPointPosition(parcast::PointD3 realPosition) = 0;
	virtual LandmarkStateListTypdef GetTargetState() = 0;
};
