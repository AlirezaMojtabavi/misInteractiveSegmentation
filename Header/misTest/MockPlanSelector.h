#pragma once
#include "IPlanSelector.h"

MOCK_BASE_CLASS(MockPlanSelector, IPlanSelector)
{
	MOCK_NON_CONST_METHOD(SelectPlan, 2,void (std::shared_ptr<ISimpleDataPackage> , std::weak_ptr<parcast::IPlan> ) );

};

