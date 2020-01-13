#pragma once

#include "PackageData.h"
#include "DateTimeMatcher.h"
namespace  parcast
{
	class PackageDataMatcher
	{
	public:
		PackageDataMatcher(const PackageData& data)
			: m_PackageData(data)
		{}

		bool operator()(const PackageData& otherData)
		{
			return IsEqual(m_PackageData, otherData);
		}

		static bool IsEqual(const PackageData& a, const PackageData& b)
		{
			return
				a.PackageUid == b.PackageUid &&
				a.PackageName == b.PackageName &&
				a.ObjectType == b.ObjectType &&
				a.SolutionUid == b.SolutionUid;
		}
	private:
		const PackageData& m_PackageData;
	};
}
