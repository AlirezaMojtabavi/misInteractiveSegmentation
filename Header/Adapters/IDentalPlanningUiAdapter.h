#pragma once

#include "PlanIndicators.h"

class ISimpleDataPackage;

namespace parcast
{
	class IPlan;

	enum class DentalPlanningStatus
	{
		Initial, ImageSelected, PlanSelected, AddingPlan, DrawingCurve
	};

	class IDentalPlanningUiAdapter
	{
	public:

		virtual ~IDentalPlanningUiAdapter() = default;

		virtual void UpdateList(const std::vector<std::shared_ptr<ISimpleDataPackage>>& packages) = 0;
		virtual void SelectPlan(std::shared_ptr<IPlan> plan, bool refreshPkg) = 0;
		virtual void SelectPackage(std::shared_ptr<ISimpleDataPackage> package) = 0;
		virtual void SetState(DentalPlanningStatus state) = 0;
		virtual void UpdatePlan(std::shared_ptr<IPlan> plan) = 0;
		virtual void UpdatePlanIndicators(const PlanIndicators& indicators) = 0;
		virtual void SetPlanCentricViewAngle(double angle) = 0;
	};

}
