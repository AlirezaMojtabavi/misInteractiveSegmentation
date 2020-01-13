#pragma once

#include "PackageItemRelData.h"

namespace parcast
{

	class IPackageItemRelDataAccess
	{
	public:
		virtual ~IPackageItemRelDataAccess() = default;
		virtual void Insert(const PackageItemRelData& data) = 0;
		virtual std::vector<PackageItemRelData> GetByPackageUid(const std::string& uid) const = 0;
	};

}
