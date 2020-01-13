#pragma once

#include "misCalculateDistance.h"

class misCalculateTargetPointDistance : public misCalculateDistance
{

public:
	void Reset(void);
	double GetDistanceTo(const double pos[3]);
	parcast::VectorD3 GetVectorTo(const double pos[3]) const;

	misCalculateTargetPointDistance(void);
	~misCalculateTargetPointDistance(void);
};