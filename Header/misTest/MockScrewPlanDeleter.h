#pragma once

#include "IScrewPlanDeleter.h"

MOCK_BASE_CLASS(MockScrewPlanDeleter, IScrewPlanDeleter)
{
	MOCK_NON_CONST_METHOD(DeleteCurrentPlan, 4, bool(bool& modifyingPlanMode,
		std::shared_ptr<ISimpleDataPackage>,
		std::shared_ptr<parcast::IPlan> planUnderEdit,
		std::weak_ptr<parcast::IPlan> currentlySelectedPlan));
};
