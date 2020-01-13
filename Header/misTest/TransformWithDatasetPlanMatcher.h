#pragma once
#include "TransformMatcher.h"
#include "ITransform.h"

namespace parcast
{

	class TransformWithDatasetPlanMatcher
	{
	public:
		TransformWithDatasetPlanMatcher(IDatasetManager* datasetManager, std::size_t packageIndex, std::size_t planIndex)
			: DatasetManager(datasetManager),
			PackageIndex(packageIndex),
			PlanIndex(planIndex)
		{
		}

		bool operator()(vtkMatrix4x4* transform) const
		{
			auto packageItem = DatasetManager->GetPackageViewingList(SimplePackages).at(PackageIndex);
			auto planUid = packageItem.planningDataProperties.at(PlanIndex).objectUID;
			auto plan = DatasetManager->GetPlanRepo()->Get(planUid).lock();
			auto trans = plan->GetTransform();
			double transMat[16];
			trans->GetMarixElements(transMat);
			auto matcher = MatrixElementwiseMatcher(transMat);
			return matcher(transform);
		}

	private:
		IDatasetManager* const DatasetManager;
		const std::size_t PackageIndex, PlanIndex;
	};

}
