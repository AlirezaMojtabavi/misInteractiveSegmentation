#pragma once

#include "IPackageImageRelDataAccess.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPackageImageRelDataAccess, IPackageImageRelDataAccess)
	{
		MOCK_NON_CONST_METHOD(InsertOrUpdate, 1, void (const PackageImageRelationship&));
		MOCK_NON_CONST_METHOD(GetByPackageUid, 1, std::vector<PackageImageRelationship>(const std::string& uid));
		MOCK_NON_CONST_METHOD(DeleteByImageUid, 1, void (const std::string& uid));
	};

}