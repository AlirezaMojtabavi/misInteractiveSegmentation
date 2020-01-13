#pragma once

#include "ChainBool.h"

namespace parcast
{

	class UpdatePlanIndicatorsEventMatcher
	{
	public:
		UpdatePlanIndicatorsEventMatcher(const PlanIndicators& inds, std::string expectedTabName, std::string expectedSubTabName)
			: ExpectedIndicators(inds),
			ExpectedTabName(expectedTabName),
			ExpectedSubTabName(expectedSubTabName) 
		{ }

		bool operator()(itk::EventObject const &event)
		{
			auto ev = dynamic_cast<misUpdatePlanIndicatorsCore const*>(&event);
			if (!ev)
				return false;

			auto received = ev->Get();

			return ChainBool().Add(ExpectedIndicators.Visibility == received.Visibility).
				Add(FloatingPointCompare::IsClose(ExpectedIndicators.PlanDiameter, received.PlanDiameter)).
				Add(FloatingPointCompare::IsClose(ExpectedIndicators.PlanCentricViewAngle, received.PlanCentricViewAngle)).
				Add(ExpectedTabName == ev->GetTabName()).
				Add(ExpectedSubTabName == ev->GetSubTabName());
		}

	private:
		PlanIndicators ExpectedIndicators;
		const std::string ExpectedTabName;
		const std::string ExpectedSubTabName;
	};

}
