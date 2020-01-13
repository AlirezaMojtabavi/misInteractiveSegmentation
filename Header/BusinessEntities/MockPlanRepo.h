#pragma once

#include "IPlanRepo.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockPlanRepo, IPlanRepo)
	{
		MOCK_NON_CONST_METHOD(CreateNewPlan, 1, std::weak_ptr<IPlan>(std::string  const& parentImageUid));
		MOCK_NON_CONST_METHOD(Get, 1, std::weak_ptr<IPlan>(std::string const& uid));
		MOCK_NON_CONST_METHOD(Delete, 1, void(std::string const& uid));
		MOCK_NON_CONST_METHOD(Clear, 0, void());
		MOCK_CONST_METHOD(GetAllPlans, 0, std::vector<std::weak_ptr<IPlan> > ());

	};

}
