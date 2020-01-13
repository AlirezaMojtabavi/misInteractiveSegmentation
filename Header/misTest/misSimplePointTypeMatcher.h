#pragma once
#include "misDistributionStruct.h"
#include "misSimplePointType.h"

namespace parcast
{
	class misSimplePointTypeMatcher
	{
	public:
		misSimplePointTypeMatcher(const misSimplePointType& data) : m_Point(data)
		{}

		static bool IsEqual(const misSimplePointType& a, const misSimplePointType& b)
		{
			return a.data[0] == b.data[0] &&
				 a.data[1] == b.data[1] &&
				a.data[2] == b.data[2];
			
		}

		bool operator()(const misSimplePointType& other) const
		{
			return IsEqual(m_Point, other);
		}
	private:
		const misSimplePointType m_Point;
	};
}

