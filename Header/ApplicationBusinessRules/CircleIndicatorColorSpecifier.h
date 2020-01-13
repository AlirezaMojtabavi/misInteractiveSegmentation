#pragma once
#include "Adapters\IPilotIndicatorColorSpecifier.h"
#include "Adapters\IPositionInPlanCoordinateSystemCalculatorGetter.h"
#include "ApplicationBusinessRules\PilotAllIndicatorsColorSpecifier.h"

class CircleIndicatorColorSpecifier : public parcast::IPilotIndicatorColorSpecifier
{
public:
	 CircleIndicatorColorSpecifier(
		std::shared_ptr<const parcast::IPositionInPlanCoordinateSystemCalculatorGetter> positionCalculator,
		const parcast::PilotAllIndicatorsColorSpecifier::ZoneThreshold& grayZoneThreshold,
		const parcast::PilotAllIndicatorsColorSpecifier::ZoneThreshold& greenZoneThreshold,
		const parcast::PilotAllIndicatorsColorSpecifier::ZoneThreshold& yellowZoneThreshold);

	IndicatorColor GetColor() const override;


	void SetPlan(std::weak_ptr<parcast::IPlan> plan) override;

private:
	std::shared_ptr<const parcast::IPositionInPlanCoordinateSystemCalculatorGetter> m_PositionCaluclator;
	std::weak_ptr<parcast::IPlan> m_Plan;
	parcast::PilotAllIndicatorsColorSpecifier::ZoneThreshold m_GreenZoneThresh, m_YellowZoneThresh, m_GrayZoneThresh;
};

