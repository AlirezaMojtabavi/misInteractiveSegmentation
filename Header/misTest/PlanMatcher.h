#pragma once

#include "FloatingPointCompare.h"
#include "BusinessEntities\Point.h"
#include "misVertebraScrewPlanData.h"

namespace parcast
{
	class PlanMatcher
	{

	public:

		explicit PlanMatcher(std::shared_ptr<misPlanData> plan) :m_Plan(plan)
		{
			
		}


		bool operator()(std::shared_ptr<misPlanData> other) const
		{
			return AreEqual(m_Plan, other);
		}

		static bool AreEqual(std::shared_ptr<misPlanData> a, std::shared_ptr<misPlanData> b)
		{
			auto plan1 = dynamic_cast<const misVertebraScrewPlanData&>(*a);
			auto plan2 = dynamic_cast<const misVertebraScrewPlanData&>(*b);

			bool result = plan1.GetUID() == plan2.GetUID();
			result = result && (plan1.GetImplantBrand() == plan2.GetImplantBrand());
			result = result && (plan1.GetObjectType() == plan2.GetObjectType());
			result = result && AreColorEqual(plan1.GetPlannigColor(), plan2.GetPlannigColor());
			result = result && FloatingPointCompare::AreCoordinatesClose(plan1.GetEntryPoint(), plan2.GetEntryPoint());
			result = result && FloatingPointCompare::AreCoordinatesClose(plan1.GetTargetPoint(), plan2.GetTargetPoint());
			result = result && (plan1.GetPlanName() == plan2.GetPlanName());
			result = result && (plan1.GetScrewVerbetraDirection() == plan2.GetScrewVerbetraDirection());
			result = result && (plan1.GetScrewVerbetraPosition() == plan2.GetScrewVerbetraPosition());
			result = result && (plan1.GetScrewDiameter() == plan2.GetScrewDiameter());
			result = result && (plan1.GetScrewLength() == plan2.GetScrewLength());
			result = result && (plan1.GetScrewSourceType() == plan2.GetScrewSourceType());
			result = result && (plan1.GetParentImageUID() == plan2.GetParentImageUID());
			result = result && (plan1.GetPlanCentricViewAngle() == plan2.GetPlanCentricViewAngle());
			return result;
		}

		static bool AreColorEqual(const misColorStruct& a, const misColorStruct& b)
		{
			return
				a.red == b.red &&
				a.green == b.green &&
				a.blue == b.blue &&
				a.alpha == b.alpha;
		}

	private:
		std::shared_ptr<misPlanData> m_Plan;
	};
}
