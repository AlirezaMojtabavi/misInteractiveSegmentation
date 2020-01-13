#pragma once

class IDatasetManager;

namespace parcast
{

	class DatasetPackagePanoramicCurveMatcher
	{
	public:
		DatasetPackagePanoramicCurveMatcher(IDatasetManager* datasetManager, std::size_t packageIndex)
			: DatasetManager(datasetManager),
			PackageIndex(packageIndex)
		{
		}

		bool operator()(const std::vector< itk::Point<double, 3> >& receivedPoints) const
		{
			auto packageUid = DatasetManager->GetPackageViewingList(SimplePackages).at(PackageIndex).packegeUID;
			auto expectedPoints = DatasetManager->GetPackageData(packageUid)->GetParametricSpline();
			return receivedPoints == expectedPoints;
		}

	private:
		IDatasetManager* const DatasetManager;
		const std::size_t PackageIndex;
	};

}