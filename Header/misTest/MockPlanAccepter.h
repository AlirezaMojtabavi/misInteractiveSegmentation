#pragma once
#include "IPlanAccepter.h"

MOCK_BASE_CLASS(MockPlanAccepter, IPlanAccepter)
{
	MOCK_NON_CONST_METHOD(AcceptPlan, 2,  void (std::weak_ptr<parcast::IPlan>, const ScrewPlanInformation& ));
};
