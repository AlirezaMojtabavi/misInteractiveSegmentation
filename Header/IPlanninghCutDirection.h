#pragma once
#include "misCroppingDirectionInVR.h"
class IPlanninghCutDirection
{
public:
	virtual void SetCroppingDirection(misCroppingDirectionInVR croppingDirection) = 0;
	virtual void UpdateCutPlanes() = 0;
	virtual ~IPlanninghCutDirection()= default;
};
