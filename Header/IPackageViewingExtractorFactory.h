#pragma once
#include "IPackagePlanRelRepo.h"
#include "IPackageViewingExtractor.h"

class IPackageViewingExtractorFactory
{
public:
	virtual std::shared_ptr<IPackageViewingExtractor> Create(
		std::shared_ptr<const ISimpleDataPackage> package,
		std::shared_ptr<parcast::IPackagePlanRelRepo> planRepo) const = 0;
};
