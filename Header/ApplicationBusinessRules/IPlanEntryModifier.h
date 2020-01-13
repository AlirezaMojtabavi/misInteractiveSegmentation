#pragma once
#include "IPackagePlanRel.h"

namespace parcast
{

	class IPlanEntryModifier
	{
	public:
		virtual ~IPlanEntryModifier() noexcept = default;
		virtual void ModifyPlanEntryPoint(std::weak_ptr<parcast::IPackagePlanRel> planRel, const std::string& imageUid,
		                                  const std::string& toolTipUid) = 0;
	};

}
