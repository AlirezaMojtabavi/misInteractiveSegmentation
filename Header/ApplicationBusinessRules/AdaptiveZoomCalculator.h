#pragma once
#include "IAdaptiveZoomCalculator.h"
#include "Adapters/IPositionInPlanCoordinateSystemCalculatorGetter.h"

namespace parcast
{

	class AdaptiveZoomCalculator : public IAdaptiveZoomCalculator
	{
	public:

		AdaptiveZoomCalculator(
			std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorGetter> positionInPlanCoordinateSystemCalculator,
			const std::function<double(double x)>& expFunction) noexcept;

		double GetZoomFactor() const override;

	private:
		std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorGetter> m_PositionInPlanCoordinateSystemCalculator;
		std::function<double(double x)> m_ExpFunction;

	};

}
