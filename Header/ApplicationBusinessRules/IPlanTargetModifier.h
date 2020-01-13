#pragma once
#include "IPackagePlanRel.h"

namespace parcast
{

	class IPlanTargetModifier
	{
	public:
		virtual ~IPlanTargetModifier() noexcept = default;
		virtual void ModifyPlanTargetPoint(std::weak_ptr<parcast::IPackagePlanRel> planRel, const std::string& imageUid,
			const std::string& toolTipUid) = 0;
		virtual void SetVirtualTipLength(double length) = 0;
	};
}
