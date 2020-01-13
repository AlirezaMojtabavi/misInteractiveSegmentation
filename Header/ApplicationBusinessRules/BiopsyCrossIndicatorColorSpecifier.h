#pragma once
#include "Adapters/IPilotIndicatorColorSpecifier.h"
#include "Adapters/IPositionInPlanCoordinateSystemCalculatorGetter.h"

namespace parcast
{

	class BiopsyCrossIndicatorColorSpecifier : public IPilotIndicatorColorSpecifier
	{
	public:
		BiopsyCrossIndicatorColorSpecifier(
			std::shared_ptr<const IPositionInPlanCoordinateSystemCalculatorGetter> positionInPlanCoordinateSystemCalculator,
			double greenRadius,
			double yellowRadius,
			double grayRadius);

		IndicatorColor GetColor() const override;
		void SetPlan(std::weak_ptr<IPlan> plan) override;

	private:
		std::shared_ptr<const IPositionInPlanCoordinateSystemCalculatorGetter> PositionInPlanCoordinateSystemCalculator;
		const double GreenRadius;
		const double YellowRadius;
		const double GrayRadius;

		std::weak_ptr<IPlan> m_Plan;
	};

}
