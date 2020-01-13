#pragma once
#include "misCalculateTargetPointDistance.h"
#include "misGuiStructures.h"
#include "ITargetDistanceMeasurement.h"
#include "Point.h"

// Target point distance indicator
class misTargetDistanceMeasurement : public ITargetDistanceMeasurement
{
public:
 	void Reset() override;
	void AdvancedTargetPointState(int state) override;
	itk::Point<double, 3> GetTargetPointPosition(int index) override;
	bool IsTargetPointActive() override;
	void TargetPointActivationOn() override;
	void TargetPointActivationOff() override;
	parcast::Vector<double> GetVectorToTargetPoint(const double* realPosition) const override ;
	void SetTargetPointPosition(parcast::PointD3 realPosition) override;
	LandmarkStateListTypdef GetTargetState( ) override;

private:
	misCalculateTargetPointDistance m_DistanceToTargetPoint;  

};

