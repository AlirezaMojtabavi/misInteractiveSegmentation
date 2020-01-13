#include "stdafx.h"
#include "PackageViewingExtractorFactory.h"
#include "IPackagePlanRelRepo.h"
#include "misPackageViewingExtractor.h"

std::shared_ptr<IPackageViewingExtractor> PackageViewingExtractorFactory::Create(
	std::shared_ptr<const ISimpleDataPackage> package, std::shared_ptr<parcast::IPackagePlanRelRepo> planRepo) const
{
	return std::make_shared<misPackageViewingExtractor>(package, planRepo);
}
