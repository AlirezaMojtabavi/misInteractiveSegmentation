#pragma once

#include "ISimpleDataPackage.h"

class INavigationPackageFinder
{
public:
	typedef std::vector< std::weak_ptr<ISimpleDataPackage> > PackagesListTypedef;

	virtual ~INavigationPackageFinder() = default;

	virtual PackageViewingListTypedef GetCorreletedPackeWith(misUID reference) const = 0;
	virtual misUID FindPackageWithOneImageUID(misUID imageUID) const = 0;
	virtual void SetPackages(const PackagesListTypedef& packages) = 0;
};
