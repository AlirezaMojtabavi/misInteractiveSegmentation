#pragma once
#include "IPlanDataAccess.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockPlanDataAccess, IPlanDataAccess)
	{
		MOCK_NON_CONST_METHOD(Insert, 1, void(const PlanData& data));
		MOCK_NON_CONST_METHOD(GetBySolutionUid, 1, std::vector<PlanData> (const std::string& uid));
	};
}