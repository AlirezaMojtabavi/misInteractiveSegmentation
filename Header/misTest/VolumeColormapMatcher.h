#pragma once
#include"VolumeColormap.h"

namespace parcast
{
	class VolumeColormapMatcher
	{
	public:
		explicit VolumeColormapMatcher(const VolumeColormap& data) : m_Data(data)
		{}

		static bool IsEqual(const VolumeColormap& a, const VolumeColormap& b)
		{
			return
				a.VolumeUid == b.VolumeUid &&
				a.AutomaticColorMode == b.AutomaticColorMode &&
				a.Color.Alpha == b.Color.Alpha &&
				a.Color.Red == b.Color.Red &&
				a.Color.Green == b.Color.Green &&
				a.Color.Blue == b.Color.Blue &&
				a.MaximumThreshold == b.MaximumThreshold&&
				a.MinimumThreshold == b.MinimumThreshold&&
				a.UseDefaultMaximumThreshold == b.UseDefaultMaximumThreshold&&
				a.UseDefaultThreshold == b.UseDefaultThreshold;
		}

		bool operator()(const VolumeColormap& other) const
		{
			return IsEqual(m_Data, other);
		}

		VolumeColormap m_Data;
	};


}

