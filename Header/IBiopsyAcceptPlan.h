#pragma once
#include "ISimpleDataPackage.h"
#include "IPlan.h"
#include "BiopsyPlanInformation.h"

namespace  parcast
{

	class IBiopsyAcceptPlan
	{
	public:
		virtual bool AcceptPlan(const BiopsyPlanInformation& planInformation, std::shared_ptr<ISimpleDataPackage>, std::shared_ptr<parcast::IPlan>
			currentlySelectedPlan) = 0;

		virtual ~IBiopsyAcceptPlan() = default;
	};
}
