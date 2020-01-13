#pragma once

#include"SegmentedImageData.h"

namespace parcast
{
	class SegmentedImageDataMatcher
	{
	public:
		explicit SegmentedImageDataMatcher(const SegmentedImageData& data) : m_Data(data)
		{}

		static bool IsEqual(const SegmentedImageData& a, const SegmentedImageData& b)
		{
			return
				a.ImageUid == b.ImageUid &&
				a.ImagePrimaryUid == b.ImagePrimaryUid &&
				a.SolutionUid == b.SolutionUid &&
				a.ImageName == b.ImageName &&
				a.Extent == b.Extent &&
				a.Spacing == b.Spacing &&
				a.Roi == b.Roi;
 		}

		bool operator()(const SegmentedImageData& other) const
		{
			return IsEqual(m_Data, other);
		}

		SegmentedImageData m_Data;
	};

}
