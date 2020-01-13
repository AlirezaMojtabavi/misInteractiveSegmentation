#include "stdafx.h"
#include "AdaptiveZoomCalculator.h"

using namespace parcast;

AdaptiveZoomCalculator::AdaptiveZoomCalculator(
	std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorGetter> positionInPlanCoordinateSystemCalculator,
	const std::function<double(double x)>& expFunction) noexcept:
	m_PositionInPlanCoordinateSystemCalculator(positionInPlanCoordinateSystemCalculator),
	m_ExpFunction(expFunction)
{
}

double AdaptiveZoomCalculator::GetZoomFactor() const
{
	if(!m_PositionInPlanCoordinateSystemCalculator->IsToolValid())
	{
		return 1.;
	}
	const auto toolTip = m_PositionInPlanCoordinateSystemCalculator->GetToolTip();
	const auto ToolHandle = m_PositionInPlanCoordinateSystemCalculator->GetPredictedTarget();
	const auto distanceToolTip = std::hypot(toolTip[0], toolTip[1]);
	const auto distanceHandleTip = std::hypot(ToolHandle[0], ToolHandle[1]);
	const auto maxDistance = std::max(distanceToolTip, distanceHandleTip);
	return m_ExpFunction(maxDistance);
}
