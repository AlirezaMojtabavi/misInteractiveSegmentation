#pragma once

#include "PackageData.h"

namespace parcast
{

	class IPackageDataAccess
	{
	public:
		virtual void InsertOrUpdate(const PackageData& inPackageData) = 0;
		virtual std::vector<PackageData> GetBySolutionUid(const std::string& solutionUid) = 0;

		virtual ~IPackageDataAccess() { }
	};

}
