#pragma once

#include "IDentalPlanningUiAppSide.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockDentalPlanningUiAppSide, IDentalPlanningUiAppSide)
	{
		MOCK_NON_CONST_METHOD(ChangeStatus, 1, void(const std::string& statusString));
		MOCK_NON_CONST_METHOD(UpdatePackageList, 1, void(const PackageViewingListTypedef& packageList));
		MOCK_NON_CONST_METHOD(SelectPackage, 1, void(const std::string& packageUid));
		MOCK_NON_CONST_METHOD(SelectPlan, 2, void(const std::string& packageUid, bool refreshPkg));
		MOCK_NON_CONST_METHOD(UpdatePlan, 1, void(std::shared_ptr<IPackagePlanRel> rel));
		MOCK_NON_CONST_METHOD(UpdatePlanIndicators, 1, void (const PlanIndicators& indicators));
		MOCK_NON_CONST_METHOD(UpdatePlanCentricViewAngle, 1, void(double angle));
	};

}
