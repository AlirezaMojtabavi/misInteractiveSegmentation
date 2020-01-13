#pragma once
#include "IPackageViewingExtractorFactory.h"

class PackageViewingExtractorFactory : public IPackageViewingExtractorFactory
{
public:
	std::shared_ptr<IPackageViewingExtractor> Create(std::shared_ptr<const ISimpleDataPackage> package,
		std::shared_ptr<parcast::IPackagePlanRelRepo> planRepo) const override;
};