#pragma once
#include"VolumeVisibility.h"

namespace parcast
{

	class VolumeVisibilityMatcher
	{
	public:
		explicit VolumeVisibilityMatcher(const VolumeVisibility& data) : m_Data(data)
		{}

		static bool IsEqual(const VolumeVisibility& a, const VolumeVisibility& b)
		{
			return
				a.Opacity2D == b.Opacity2D &&
				a.Opacity3D == b.Opacity3D &&
				a.Viewing == b.Viewing&&
				a.Visibility2D == b.Visibility2D&&
				a.Visibility3D == b.Visibility3D;
		}

		bool operator()(const VolumeVisibility& other) const
		{
			return IsEqual(m_Data, other);
		}

		VolumeVisibility m_Data;
	};

}