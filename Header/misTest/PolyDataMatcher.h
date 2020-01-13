#pragma once

#include "CompareCollections.h"
#include "misPolyData.h"

namespace parcast
{

	class PolyDataMatcher
	{
	public:
		static void CheckEqual(const misPolyData& a, const misPolyData& b)
		{
			BOOST_CHECK(AreEqual(a, b));
		}

		static bool AreEqual(const misPolyData& a, const misPolyData& b)
		{
			return true;
		}

	private:
	};

}
