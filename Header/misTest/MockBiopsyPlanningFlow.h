#pragma once

#include "IBiopsyPlanningFlow.h"

MOCK_BASE_CLASS(MockBiopsyPlanningFlow, IBiopsyPlanningFlow)
{
	MOCK_NON_CONST_METHOD(StartPlanFlow, 3, void(std::shared_ptr<IPlan> ,	misCineDirection ,	misCroppingDirectionInVR ));
	MOCK_NON_CONST_METHOD(SetPlanFlowSlider, 3, void(const double& , std::weak_ptr<IPlan> ,misCineDirection planFlowDirection));
	MOCK_NON_CONST_METHOD(StopPlanFlow, 0, void());
};
