#pragma once
#include "misDataProdecureEnum.h"
#include "misPlanData.h"
#include "IPlanninghCutDirection.h"

class IBiopsyPlanningFlow
{
public:
	virtual ~IBiopsyPlanningFlow() = default;
	virtual void StartPlanFlow(std::shared_ptr<IPlan> planReadytoFlow,
	                           misCineDirection planFlowDirection,
	                           misCroppingDirectionInVR croppingDir = NoCut) = 0;
	virtual void SetPlanFlowSlider(const double& value, std::weak_ptr<IPlan> plnData,
	                               misCineDirection planFlowDirection) = 0;
	virtual void StopPlanFlow() = 0;
};
