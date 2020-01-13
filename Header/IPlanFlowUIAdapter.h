#pragma once
#include "misCroppingDirectionInVR.h"
class IPlanFlowUIAdapter
{
public:
	virtual ~IPlanFlowUIAdapter() = default;

	virtual void SendLastPointInfo(double value) = 0;
	virtual void SetPlanFlowEndDirection(const misCineDirection &direction) = 0;
	virtual void RefreshGUI() = 0;
	virtual void UpdataCroppingDirectionInGUI(misCroppingDirectionInVR croppingDirection) = 0;
};

