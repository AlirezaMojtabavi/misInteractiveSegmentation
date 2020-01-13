#pragma once

#include "IPackageDataAccess.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPackageDataAccess, IPackageDataAccess)
	{
		MOCK_NON_CONST_METHOD(InsertOrUpdate, 1, void(const PackageData & inPackageData));
		MOCK_NON_CONST_METHOD(GetBySolutionUid, 1, std::vector<PackageData>(const std::string& solutionUid));
	};

}