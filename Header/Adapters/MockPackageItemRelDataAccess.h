#pragma once
#include "IPackageItemRelDataAccess.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockPackageItemRelDataAccess, IPackageItemRelDataAccess)
	{
		MOCK_NON_CONST_METHOD(Insert, 1, void(const PackageItemRelData& data));
		MOCK_CONST_METHOD(GetByPackageUid, 1, std::vector<PackageItemRelData> (const std::string& uid));
	};
}
