#pragma once
#include"ImageContainedVisibility.h"

namespace parcast
{
	class ImageContainedVisibilityMatcher
	{
	public:
		explicit ImageContainedVisibilityMatcher(const ImageContainedVisibility& data) : m_Data(data)
		{}

		static bool IsEqual(const ImageContainedVisibility& a, const ImageContainedVisibility& b)
		{
			return
				a.ImageContainedPolyDataUid == b.ImageContainedPolyDataUid&&
				a.ThreeDModelUid == b.ThreeDModelUid&&
				a.Opacity2D == b.Opacity2D &&
				a.Opacity3D == b.Opacity3D &&
				a.Visibility2D == b.Visibility2D&&
				a.Visibility3D == b.Visibility3D;
		}

		bool operator()(const ImageContainedVisibility& other) const
		{
			return IsEqual(m_Data, other);
		}

		ImageContainedVisibility m_Data;
	};
}