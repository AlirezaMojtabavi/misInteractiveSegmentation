#pragma once
#include "IVirtualTipLengthCalculator.h"

namespace parcast
{

	class VirtualTipLengthCalculatorEuclidean : public IVirtualTipLengthCalculator
	{
	public:
		double GetLength(
			parcast::PointD3 const& toolPosition,
			parcast::VectorD3 toolDirection,
			parcast::PointD3 targetPosition,
			double const& targetRadius) const override;

	};

}