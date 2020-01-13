#pragma once
#include "BusinessEntities\Point.h"

class IVirtualTipLengthCalculator
{
public:
	virtual ~IVirtualTipLengthCalculator() = default;
	virtual double GetLength(
		parcast::PointD3 const& toolPosition,
		parcast::VectorD3 toolDirection,
		parcast::PointD3 targetPosition,
		double const& targetRadius) const = 0;
};
