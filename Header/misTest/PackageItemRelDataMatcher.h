#pragma once
#include"PackageItemRelData.h"

namespace parcast
{

	class PackageItemRelDataMatcher
	{
	public:
		explicit PackageItemRelDataMatcher(const PackageItemRelData& data) : m_Data(data)
		{}

		static bool IsEqual(const PackageItemRelData& a, const PackageItemRelData& b)
		{
			return
				a.PackageUid == b.PackageUid &&
				a.ItemUid == b.ItemUid &&
				a.Opacity2D == b.Opacity2D &&
				a.Opacity3D == b.Opacity3D &&
				a.Visibility2D == b.Visibility2D &&
				a.Visibility3D == b.Visibility3D;
		}

		bool operator()(const PackageItemRelData& other) const
		{
			return IsEqual(m_Data, other);
		}

		PackageItemRelData m_Data;
	};

}
