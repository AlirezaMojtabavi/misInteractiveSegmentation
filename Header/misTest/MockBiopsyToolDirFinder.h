#pragma once

#include "IBiopsyToolDirFinder.h"
#include <BusinessEntities/Point.h>

namespace parcast
{
	MOCK_BASE_CLASS(MockBiopsyToolDirFinder, IBiopsyToolDirFinder)
	{
		using PairOfPoints = std::pair<parcast::PointD3, parcast::PointD3>;
		MOCK_CONST_METHOD(GetSortedPoints, 2, PairOfPoints(const std::pair<parcast::PointD3, parcast::PointD3>&,  const parcast::PointD3& imagePos));
	};

}
