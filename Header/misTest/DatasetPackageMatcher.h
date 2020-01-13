#pragma once

namespace parcast
{

	class DatasetPackageMatcher
	{
	public:
		DatasetPackageMatcher(IDatasetManager* datasetManager, std::size_t packageIndex)
			: DatasetManager(datasetManager),
			PackageIndex(packageIndex)
		{
		}

		bool operator()(std::shared_ptr<ISimpleDataPackage> receivedPackage) const
		{
			auto packageUid = DatasetManager->GetPackageViewingList(SimplePackages).at(PackageIndex).packegeUID;
			auto expectedPackage = DatasetManager->GetPackageData(packageUid);
			return expectedPackage == receivedPackage;
		}

	private:
		IDatasetManager* const DatasetManager;
		const std::size_t PackageIndex;
	};

}