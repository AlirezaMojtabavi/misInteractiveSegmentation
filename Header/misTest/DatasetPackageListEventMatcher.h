#pragma once

#include "misPackageViewingItemsStrctMatcher.h"
#include "IDatasetManager.h"
#include "misCoreEvents.h"

namespace parcast
{

	class DatasetPackageListEventMatcher
	{
	public:
		DatasetPackageListEventMatcher(
			IDatasetManager* datasetManager, PackageListViewingType viewingType,
			std::string expectedTabName, std::string expectedSubTabName)
			: DatasetManager(datasetManager),
			ViewingType(viewingType),
			ExpectedTabName(expectedTabName),
			ExpectedSubTabName(expectedSubTabName)
		{
		}

		bool operator()(itk::EventObject const &event)
		{
			auto pkgListEv = dynamic_cast<misPackageListEventCore const*>(&event);
			if (!pkgListEv)
				return false;

			auto receivedList = pkgListEv->Get();
			auto expectedList = DatasetManager->GetPackageViewingList(ViewingType);
			return ChainBool(std::cout, "DatasetPackageListEventMatcher").Add(std::equal(receivedList.cbegin(), receivedList.cend(),
				expectedList.cbegin(), misPackageViewingItemsStrctMatcher::IsEqual)).
				Add(ExpectedTabName == pkgListEv->GetTabName()).
				Add(ExpectedSubTabName == pkgListEv->GetSubTabName());
		}

	private:
		IDatasetManager* const DatasetManager;
		const PackageListViewingType ViewingType;
		const std::string ExpectedTabName;
		const std::string ExpectedSubTabName;
	};

}
