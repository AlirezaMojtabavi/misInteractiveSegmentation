#pragma once

#include "PackageImageRelationship.h"

namespace parcast
{

	class IPackageImageRelDataAccess
	{
	public:
		virtual void InsertOrUpdate(const PackageImageRelationship& data) = 0;
		virtual std::vector<PackageImageRelationship> GetByPackageUid(const std::string& uid) = 0;
		virtual void DeleteByImageUid(const std::string& uid) = 0;

		virtual ~IPackageImageRelDataAccess() = default;
	};

}
