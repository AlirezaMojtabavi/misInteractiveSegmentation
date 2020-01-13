#include "stdafx.h"
#include "misNavigationPackageFinder.h"

#include "ICoordinateSystemCorrelationManager.h"
#include "misDataSetManager.h"
#include "misPackageViewingExtractor.h"

misNavigationPackageFinder::misNavigationPackageFinder(PackagesListTypedef packages,
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > cSCorrelationManager)
:m_packages(packages), m_CorrelationManager(cSCorrelationManager)
{
}


misNavigationPackageFinder::~misNavigationPackageFinder()
{
}

PackageViewingListTypedef misNavigationPackageFinder::GetCorreletedPackeWith(misUID reference)const
{

	PackageViewingListTypedef allPackagesViewingList;
 	for(auto package: m_packages)
	{
		 if(package.expired())
			 continue;
		auto extractor = misPackageViewingExtractor(package.lock(), misDatasetManager::GetInstance()->GetPackagePlanRelRepo());
		auto packageViewingStr = extractor.GetViewingPart();

		for (misShortImageViewingStrct imagePropItr : packageViewingStr.imageProperties)
		{
			auto trans = m_CorrelationManager->GetTransform(reference, imagePropItr.objectUID);
			if (trans->IsValid())
			{
				allPackagesViewingList.push_back(packageViewingStr);
				break;
			}
		}
	}
	return allPackagesViewingList;

}

misUID misNavigationPackageFinder::FindPackageWithOneImageUID(misUID imageUID)const
{
	for (auto packeItem : m_packages)
	{
		if(packeItem.expired())
			continue;
		misPackageViewingExtractor extractor(packeItem.lock(), misDatasetManager::GetInstance()->GetPackagePlanRelRepo());
		auto images = extractor.GetViewingPart().imageProperties;
		auto foundedRegisteredImage = std::find_if(images.cbegin(), images.cend(), 
			[&](const misShortImageViewingStrct& image)->bool
		{
			return image.objectUID == imageUID;
		});
		if (foundedRegisteredImage != images.cend())
		{
			return   extractor.GetViewingPart().packegeUID;
		}

	}
	return "";
}

void misNavigationPackageFinder::SetPackages(const PackagesListTypedef& packages)
{
	m_packages = packages;
}

 