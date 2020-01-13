#pragma once
#include "Adapters/IPilotIndicatorColorSpecifier.h"
#include "Adapters/IPositionInPlanCoordinateSystemCalculatorGetter.h"

namespace parcast
{

	class BiopsyDepthIndicatorColorSpecifier : public IPilotIndicatorColorSpecifier
	{
	public:
		BiopsyDepthIndicatorColorSpecifier(
			std::shared_ptr<const IPositionInPlanCoordinateSystemCalculatorGetter> positionInPlanCoordinateSystemCalculator,
			double planZoneRadius);
		IndicatorColor GetColor() const override;
		void SetPlan(std::weak_ptr<IPlan> plan) override;

	private:
		std::shared_ptr<const IPositionInPlanCoordinateSystemCalculatorGetter> PositionInPlanCoordinateSystemCalculator;
		const double PlanZoneRadius;
		std::weak_ptr<IPlan> m_Plan;
	};

}