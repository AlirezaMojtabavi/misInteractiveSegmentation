#pragma once
#include "IPackageConfirmer.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockPackageConfirmer, IPackageConfirmer)
	{
		MOCK_NON_CONST_METHOD(IsConfirmed, 1, bool(std::shared_ptr<ISimpleDataPackage> pkg));
	};
}