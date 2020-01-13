#pragma once
#include"VolumeData.h"

namespace parcast
{
	class VolumeDataMatcher
	{
	public:
		explicit VolumeDataMatcher(const VolumeData& data) : m_Data(data)
		{}

		static bool IsEqual(const VolumeData& a, const VolumeData& b)
		{
			return
				a.VolumeUid == b.VolumeUid &&
				a.ImageUid == b.ImageUid;
		}

		bool operator()(const VolumeData& other) const
		{
			return IsEqual(m_Data, other);
		}

		VolumeData m_Data;
	};


}

