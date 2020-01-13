#pragma once
#include "IPositionInPlanCoordinateSystemCalculatorSetter.h"
#include "IPositionInPlanCoordinateSystemCalculatorGetter.h"

namespace parcast
{

	class PositionInPlanCoordinateSystemCalculator :
		public IPositionInPlanCoordinateSystemCalculatorSetter,
		public IPositionInPlanCoordinateSystemCalculatorGetter
	{
	public:
		PositionInPlanCoordinateSystemCalculator(
			std::weak_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager);

		void SetPlan(std::weak_ptr<IPlan> plan) override;
		void SetToolTipCoordinateSystem(const std::string& toolTipCoordSys) override;
		PointD3 GetToolTip() const override;
		PointD3 GetPredictedTarget() const override;
		std::shared_ptr<const ITransform> GetImageToPlanTransform() const override;
		bool IsToolValid() const override;

	private:
		void Calculate();

		bool m_ToolValid = false;
		PointD3 m_ToolTip;
		PointD3 m_PredictedTarget;
		std::weak_ptr<IPlan> m_Plan;
		std::string m_ToolTipCoordinateSys;
		std::weak_ptr<ICoordinateSystemCorrelationManager<std::string>> m_CorrelationManager;
	};

}