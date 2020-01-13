#pragma once

#include "BusinessEntities\Point.h"

namespace parcast
{

	class IBiopsyToolDetector
	{
	public:
		virtual boost::optional<std::pair<PointD3, PointD3>> Detect(const std::vector<PointD3>& points) const = 0;
	};

}