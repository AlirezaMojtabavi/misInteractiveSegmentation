#pragma once

namespace parcast
{
	class PanoramicDataMatcher
	{
	public:
		explicit PanoramicDataMatcher(const PanoramicData& data) : m_PanoramicData(data) {}

		bool operator()(const PanoramicData& other) const
		{
			return IsEqual(m_PanoramicData, other);
		}

		static bool IsEqual(const PanoramicData& a, const PanoramicData& b)
		{
			return
				a.ImageUid == b.ImageUid &&
				a.NumberOfPoints == b.NumberOfPoints &&
				a.Points == b.Points;
		}

	private:
		PanoramicData m_PanoramicData;

	};
}
