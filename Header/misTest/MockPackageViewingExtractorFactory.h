#pragma once
#include "IPackageViewingExtractorFactory.h"

MOCK_BASE_CLASS(MockPackageViewingExtractorFactory, IPackageViewingExtractorFactory)
{
	MOCK_CONST_METHOD(Create, 2, std::shared_ptr<IPackageViewingExtractor>(
		std::shared_ptr<const ISimpleDataPackage> package,
		std::shared_ptr<parcast::IPackagePlanRelRepo> planRepo))
};
