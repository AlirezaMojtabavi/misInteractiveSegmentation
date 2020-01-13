#pragma once

#include "IBiopsyToolDirFinder.h"

namespace parcast
{
	class BiopsyToolDirFinder : public IBiopsyToolDirFinder
	{
	public:
		std::pair<parcast::PointD3, parcast::PointD3> GetSortedPoints(
			const std::pair<parcast::PointD3, parcast::PointD3>&,
			const PointD3& imagePos) const override;
	};
}