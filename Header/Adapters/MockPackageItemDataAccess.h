#pragma once
#include "IPackageItemDataAccess.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockPackageItemDataAccess, IPackageItemDataAccess)
	{
		MOCK_NON_CONST_METHOD(InsertIfNotExists, 1, void(const std::string& uid));
	};
}
