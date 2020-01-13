#pragma once
#include "IPackageViewingExtractor.h"

MOCK_BASE_CLASS(MockPackageViewingExtractor, IPackageViewingExtractor)
{
	MOCK_CONST_METHOD(GetViewingPart, 0, misPackageViewingItemsStrct());
};
