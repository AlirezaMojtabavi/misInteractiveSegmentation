#pragma once

#include "PlanData.h"

namespace parcast
{

	class IPlanDataAccess
	{
	public:
		virtual ~IPlanDataAccess() = default;

		virtual void Insert(const PlanData& data) = 0;
		virtual std::vector<PlanData> GetBySolutionUid(const std::string& uid) = 0;
	};

}
