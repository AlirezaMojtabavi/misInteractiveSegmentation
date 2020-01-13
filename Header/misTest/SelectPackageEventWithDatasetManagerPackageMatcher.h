#pragma once

namespace parcast
{

	class SelectPackageEventWithDatasetManagerPackageMatcher
	{
	public:
		SelectPackageEventWithDatasetManagerPackageMatcher(
			IDatasetManager* datasetManager, std::size_t packageIndex,
			std::string expectedTabName, std::string expectedSubTabName)
			: DatasetManager(datasetManager),
			PackageIndex(packageIndex),
			ExpectedTabName(expectedTabName),
			ExpectedSubTabName(expectedSubTabName)
		{
		}

		bool operator()(itk::EventObject const &event)
		{
			auto selPkgEv = dynamic_cast<misSelectedPackageEventCore const*>(&event);
			if (selPkgEv == nullptr)
				return false;

			auto packageUid = DatasetManager->GetPackageViewingList(SimplePackages).at(PackageIndex).packegeUID;
			auto expectedPackage = DatasetManager->GetPackageData(packageUid);
			return ChainBool(std::cout, "SelectPackageEventMatcher").Add(expectedPackage->GetObjectUID() == selPkgEv->Get()).
				Add(ExpectedTabName == selPkgEv->GetTabName()).
				Add(ExpectedSubTabName == selPkgEv->GetSubTabName());
		}

	private:
		IDatasetManager* const DatasetManager;
		const std::size_t PackageIndex;
		const std::string ExpectedTabName;
		const std::string ExpectedSubTabName;
	};

}