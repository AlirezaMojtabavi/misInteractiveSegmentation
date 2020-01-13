#pragma once
#include "IDatasetManager.h"
#include "INavigationPackageFinder.h"

class misNavigationPackageFinder :public INavigationPackageFinder
{
public:
	misNavigationPackageFinder(PackagesListTypedef packages,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > cSCorrelationManager);
	~misNavigationPackageFinder();
	virtual PackageViewingListTypedef GetCorreletedPackeWith(misUID reference) const override;
	misUID FindPackageWithOneImageUID(misUID imageUID) const override;
	void SetPackages(const PackagesListTypedef& packages) override;
private:

	PackagesListTypedef m_packages;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CorrelationManager;
};

