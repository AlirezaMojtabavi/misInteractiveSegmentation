#pragma once
#include "PackageImageContainedData.h"

namespace parcast
{
	class IPackageImageContainedDataAccess
	{
	public:

		virtual ~IPackageImageContainedDataAccess() = default;
		virtual void Insert(const PackageImageContainedData& data) = 0;
		virtual std::vector<PackageImageContainedData> GetByPackageUid(const std::string& uid) const = 0;

	};
}