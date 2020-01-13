#pragma once

namespace parcast
{

	class SelectPlanEventWithDatasetManagerPlanMatcher
	{
	public:
		SelectPlanEventWithDatasetManagerPlanMatcher(
			IDatasetManager* datasetManager,
			std::size_t packageIndex,
			std::size_t planIndex,
			std::string expectedTabName,
			std::string expectedSubTabName)
			: DatasetManager(datasetManager),
			PackageIndex(packageIndex),
			PlanIndex(planIndex),
			ExpectedTabName(expectedTabName),
			ExpectedSubTabName(expectedSubTabName)
		{
		}

		bool operator()(itk::EventObject const &event)
		{
			auto selPlanEv = dynamic_cast<misSelectedPlanEventCore const*>(&event);
			if (selPlanEv == nullptr)
				return false;

			auto packageItem = DatasetManager->GetPackageViewingList(SimplePackages).at(PackageIndex);
			auto planUid = packageItem.planningDataProperties.at(PlanIndex).objectUID;

			return ChainBool().
				Add(planUid == selPlanEv->Get()).
				Add(ExpectedTabName == selPlanEv->GetTabName()).
				Add(ExpectedSubTabName == selPlanEv->GetSubTabName());
		}

	private:
		IDatasetManager* const DatasetManager;
		const std::size_t PackageIndex, PlanIndex;
		const std::string ExpectedTabName;
		const std::string ExpectedSubTabName;
	};

}