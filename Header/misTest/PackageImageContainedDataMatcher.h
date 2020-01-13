#pragma once
#pragma once
#include"PackageImageContainedData.h"

namespace parcast
{

	class PackageImageContainedDataMatcher
	{
	public:
		explicit PackageImageContainedDataMatcher(const PackageImageContainedData& data) : m_Data(data)
		{}

		static bool IsEqual(const PackageImageContainedData& a, const PackageImageContainedData& b)
		{
			return
				a.PackageUid == b.PackageUid &&
				a.ImageContainedPolyDataUid == b.ImageContainedPolyDataUid &&
				a.ImageUid == b.ImageUid;

		}

		bool operator()(const PackageImageContainedData& other) const
		{
			return IsEqual(m_Data, other);
		}

		PackageImageContainedData m_Data;
	};

}
