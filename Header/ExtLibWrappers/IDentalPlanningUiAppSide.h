#pragma once

#include "misPackageViewingItemsStrct.h"
#include "PlanIndicators.h"

class ISimpleDataPackage;

namespace parcast
{
	class IPackagePlanRel;

	class IDentalPlanningUiAppSide
	{
	public:
		virtual ~IDentalPlanningUiAppSide() = default;

		virtual void ChangeStatus(const std::string& statusString) = 0;
		virtual void UpdatePackageList(const PackageViewingListTypedef& packageList) = 0;
		virtual void SelectPackage(const std::string& packageUid) = 0;
		virtual void SelectPlan(const std::string& planeUid, bool refreshPkg) = 0;
		virtual void UpdatePlan(std::shared_ptr<IPackagePlanRel> rel) = 0;
		virtual void UpdatePlanIndicators(const PlanIndicators& indicators) = 0;
		virtual void UpdatePlanCentricViewAngle(double angle) = 0;
	};

}
