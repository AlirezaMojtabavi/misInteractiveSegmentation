#pragma once
#include "BusinessEntities\Point.h"

namespace parcast
{
	class IBiopsyToolTransformCalculatorTracker
	{
	public:
		virtual ~IBiopsyToolTransformCalculatorTracker() = default;
		virtual void GetTransform( const std::pair<parcast::PointD3, parcast::PointD3>& points, double trans[4][4]) = 0;
		virtual void SetTrackerUid(const std::string& uid) = 0;
	};
}
