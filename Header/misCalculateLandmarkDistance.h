#pragma once

#include "misCalculateDistance.h"
#include "vector.h"

class misCalculateLandmarkDistance :public misCalculateDistance
{

public:
	void Reset(void) override;
	auto GetNearestLandmarkID(parcast::PointD3 pos) -> int;
	double GetDistanceTo(parcast::PointD3 pos);
	parcast::VectorD3 GetVectorTo(parcast::PointD3 pos);
	misCalculateLandmarkDistance();

private:
	int m_NearestLandmark;
	const double nearestThresholdWarning;
	parcast::VectorD3 m_VectorTo;

};

