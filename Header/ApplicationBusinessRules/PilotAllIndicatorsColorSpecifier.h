#pragma once
#include "Adapters/IPilotIndicatorColorSpecifier.h"
#include "Adapters/IPositionInPlanCoordinateSystemCalculatorGetter.h"

namespace parcast
{

	class PilotAllIndicatorsColorSpecifier : public IPilotIndicatorColorSpecifier
	{
	public:

		struct ZoneThreshold
		{
			ZoneThreshold(double h, double r);
			ZoneThreshold(const ZoneThreshold& other);

			bool ToolTipIsInside(const PointD3& toolTip) const;
			bool ToolHandleIsInside(const PointD3& toolHandle) const;
			double GetHeight() const;
			double GetRadius() const;

		private:
			double m_Height, m_Radius;
		};

		PilotAllIndicatorsColorSpecifier(
			std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorGetter> positionInPlanCoordinateSystemCalculator,
			const ZoneThreshold& grayZoneThreshold,
			const ZoneThreshold& greenZoneThreshold,
			const ZoneThreshold& yellowZoneThreshold);

		IndicatorColor GetColor() const override;
		void SetPlan(std::weak_ptr<IPlan> plan) override;

	private:
		std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorGetter> m_PositionInPlanCoordinateSystemCalculator;
		ZoneThreshold m_GreenZoneThresh, m_YellowZoneThresh, m_GrayZoneThresh;
		std::weak_ptr<IPlan> m_Plan;

	};

}
