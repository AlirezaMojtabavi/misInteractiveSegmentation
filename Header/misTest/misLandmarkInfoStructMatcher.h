#pragma once
#include "misDistributionStruct.h"




namespace parcast
{
	class misLandmarkInfoStructMatcher
	{
	public:
		misLandmarkInfoStructMatcher(const misLandmarkInfoStruct& data) : m_Point(data)
		{}

		static bool IsEqual(const misLandmarkInfoStruct& a, const misLandmarkInfoStruct& b)
		{
			return a.CurrentPosition[0] == b.CurrentPosition[0] &&
				a.CurrentPosition[1] == b.CurrentPosition[1] &&
				a.CurrentPosition[2] == b.CurrentPosition[2];

		}

		bool operator()(const misLandmarkInfoStruct& other) const
		{
			return IsEqual(m_Point, other);
		}
	private:
		const misLandmarkInfoStruct m_Point;
	};
}


