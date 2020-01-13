#pragma once
#include"ImageContainedData.h"

namespace parcast
{
	class ImageContainedDataMatcher
	{
	public:
		explicit ImageContainedDataMatcher(const ImageContainedData& data) : m_Data(data)
		{}

		static bool IsEqual(const ImageContainedData& a, const ImageContainedData& b)
		{
			return
				a.ImageContainedPolyDataUid == b.ImageContainedPolyDataUid &&
				a.ImageByteAnalysisUid == b.ImageByteAnalysisUid &&
				a.ImageUid == b.ImageUid;
		}

		bool operator()(const ImageContainedData& other) const
		{
			return IsEqual(m_Data, other);
		}

		ImageContainedData m_Data;
	};


}

