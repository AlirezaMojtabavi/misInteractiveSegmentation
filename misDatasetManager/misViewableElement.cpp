#include "stdafx.h"
#include "..\Header\misViewableElement.h"
#include "misConfirmedImageCounter.h"
#include "misDataSetManager.h"
#include "misPackageViewingExtractor.h"

misViewableElement::misViewableElement(const std::vector<std::shared_ptr<ISimpleDataPackage>> packges,
	const std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>>
	coordinateSystemCorrelationManagerSCorrelationManager, std::shared_ptr<IConfirmedImageCounter> counter)
	:m_Packges(packges), m_CSCorrelationManager(coordinateSystemCorrelationManagerSCorrelationManager),
m_Counter(counter)
{
}

std::vector< misPackageViewingItemsStrct > misViewableElement::GetPackageViewingList(PackageListViewingType viewingType)
{
	std::vector< misPackageViewingItemsStrct > allPackagesViewingList;
	for (auto packge: m_Packges)
	{
		misPackageViewingExtractor extractor(packge, misDatasetManager::GetInstance()->GetPackagePlanRelRepo());
		auto packageViewingStr = extractor.GetViewingPart();

		if (SimplePackages == viewingType &&
			misHybridPackageType == packge->GetObjectType())
		{
			bool confirmed = m_Counter->IsThereAnyUnconfirmedImage(packge);
			if (!confirmed)
			{
				continue;
			}
			allPackagesViewingList.push_back(packageViewingStr);
		}
		else if (CompletePackages == viewingType ||
			CompleteEvenUnConfirmed == viewingType)
			allPackagesViewingList.push_back(packageViewingStr);
	}
	return allPackagesViewingList;
}
