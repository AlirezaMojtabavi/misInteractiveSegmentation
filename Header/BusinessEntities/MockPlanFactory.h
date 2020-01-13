#pragma once

#include "IPlanFactory.h"

namespace parcast
{


	MOCK_BASE_CLASS(MockPlanFactory, IPlanFactory)
	{
		MOCK_NON_CONST_METHOD(CreateNewPlan, 1, std::shared_ptr<IPlan>(std::string  const& parentImageUid));
	};

}