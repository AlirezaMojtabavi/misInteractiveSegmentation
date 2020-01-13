#pragma once
 
#include "misObjectRangeStr.h"

namespace parcast
{

	class RangeStructMatcher
	{
	public:

		RangeStructMatcher(const misObjectRangeStr& range)
			: m_Range(range)
		{ }

		bool operator()(const misObjectRangeStr range)
		{
			return IsEqual(m_Range, range);
		}

		static bool IsEqual(const misObjectRangeStr range1, const misObjectRangeStr range2)
		{
			return true;
		}

	private:
		misObjectRangeStr m_Range;
 	};

}
