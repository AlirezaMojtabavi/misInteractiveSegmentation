#pragma once

#include "IDentalPlanningUiAdapter.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockDentalPlanningUiAdapter, IDentalPlanningUiAdapter)
	{
		MOCK_NON_CONST_METHOD(UpdateList, 1, void(const std::vector<std::shared_ptr<ISimpleDataPackage>>& packages));
		MOCK_NON_CONST_METHOD(SelectPlan, 2, void(std::shared_ptr<IPlan> plan, bool refreshPkg));
		MOCK_NON_CONST_METHOD(SelectPackage, 1, void(std::shared_ptr<ISimpleDataPackage> package));
		MOCK_NON_CONST_METHOD(SetState, 1, void(DentalPlanningStatus state));
		MOCK_NON_CONST_METHOD(UpdatePlan, 1, void(std::shared_ptr<IPlan> plan));
		MOCK_NON_CONST_METHOD(UpdatePlanIndicators, 1, void (const PlanIndicators& indicators));
		MOCK_NON_CONST_METHOD(SetPlanCentricViewAngle, 1, void(double angle));
	};

}

