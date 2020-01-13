#pragma once
#include "LandmarkData.h"
#include "VectorMatcher.h"

namespace parcast
{
	class LandmarkDataMatcher
	{
	public:
		LandmarkDataMatcher(const LandmarkData& data): m_LandmarkData(data)
		{}

		static bool IsEqual(const LandmarkData& a, const LandmarkData& b)
		{
			return
				a.PackageUid == b.PackageUid &&
				a.Type == b.Type &&
				VectorMatcher<Point<double, 3>, Point<double, 3>>::IsEqual(a.Position, b.Position);
		}

		bool operator()(const LandmarkData& other) const
		{
			return IsEqual(m_LandmarkData, other);
		}
	private:
		const LandmarkData& m_LandmarkData;
	};
}
