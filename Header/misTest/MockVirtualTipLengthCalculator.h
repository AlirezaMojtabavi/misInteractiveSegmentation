#pragma once
#include "IVirtualTipLengthCalculator.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockVirtualTipLengthCalculator, IVirtualTipLengthCalculator)
	{
		MOCK_CONST_METHOD(GetLength, 4, double(
			PointD3 const& toopPosition, VectorD3 toolDirection, PointD3 targetPosition, double const& targetRadius))
	};

}