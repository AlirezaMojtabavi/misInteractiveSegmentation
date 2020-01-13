#pragma once
#include "PackageVolumeData.h"

namespace parcast
{
	class IPackageVolumeDataAccess
	{
	public:
		virtual ~IPackageVolumeDataAccess() = default;
		virtual void Insert(const PackageVolumeData& data) = 0;
		virtual std::vector<PackageVolumeData> GetByPackageUid(const std::string& uid) const = 0;
	};
}
