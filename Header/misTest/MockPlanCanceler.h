#pragma once
#include "IPlanCanceler.h"

MOCK_BASE_CLASS(MockPlanCanceler, IPlanCanceler)
{
	MOCK_NON_CONST_METHOD(CancelPlan, 2 ,void(std::shared_ptr<ISimpleDataPackage> , std::weak_ptr<parcast::IPlan> ) );


};
