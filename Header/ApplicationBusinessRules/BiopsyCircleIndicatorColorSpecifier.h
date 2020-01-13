#pragma once
#include "IPlan.h"
#include "Adapters/IPositionInPlanCoordinateSystemCalculatorGetter.h"
#include "Adapters/IPilotIndicatorColorSpecifier.h"

namespace parcast
{

	class BiopsyCircleIndicaorColorSpecifier : public parcast::IPilotIndicatorColorSpecifier
	{
	public:
		explicit BiopsyCircleIndicaorColorSpecifier(
			std::shared_ptr<const IPositionInPlanCoordinateSystemCalculatorGetter> positionCalculator);

		IndicatorColor GetColor() const override;
		void SetPlan(std::weak_ptr<parcast::IPlan> plan) override;

	private:
		std::shared_ptr<const parcast::IPositionInPlanCoordinateSystemCalculatorGetter> PositionCaluclator;
		std::weak_ptr<parcast::IPlan> m_Plan;
	};

}

