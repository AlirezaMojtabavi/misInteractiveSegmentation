#pragma once
#include "BusinessEntities\Point.h"

namespace parcast
{
	class IBiopsyToolDirFinder
	{
	public:
		virtual std::pair<parcast::PointD3, parcast::PointD3> GetSortedPoints(
			const std::pair<parcast::PointD3, parcast::PointD3>&,
			const parcast::PointD3& imagePos) const = 0;
	};
}
