#pragma once
#include "misTest/misPackageViewingItemsStrctMatcher.h"

class IPackageViewingExtractor
{
public:
	virtual misPackageViewingItemsStrct GetViewingPart() const = 0;
};
