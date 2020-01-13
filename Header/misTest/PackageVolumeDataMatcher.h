#pragma once
#pragma once
#include"PackageVolumeData.h"

namespace parcast
{

	class PackageVolumeDataMatcher
	{
	public:
		explicit PackageVolumeDataMatcher(const PackageVolumeData& data) : m_Data(data)
		{}

		static bool IsEqual(const PackageVolumeData& a, const PackageVolumeData& b)
		{
			return
				a.PackageUid == b.PackageUid &&
				a.VolumeUid == b.VolumeUid &&
				a.ImageUid == b.ImageUid;
				
		}

		bool operator()(const PackageVolumeData& other) const
		{
			return IsEqual(m_Data, other);
		}

		PackageVolumeData m_Data;
	};

}
