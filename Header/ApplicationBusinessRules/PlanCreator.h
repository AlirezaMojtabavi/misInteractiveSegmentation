#pragma once
#include "IPlanCreator.h"

class IDatasetManager;
class ISimpleDataPackage;

namespace parcast
{
	class PlanCreator : public IPlanCreator
	{
	public:
		PlanCreator(IDatasetManager* datasetMgr, std::weak_ptr<IPackageDataVisualizer> packageVisualizer);
		std::shared_ptr<IPlan> CreatePlan(const misUID imageUid, std::shared_ptr<ISimpleDataPackage> currentPkg) override;
	private:
		IDatasetManager* m_DatasetMgr;
		std::weak_ptr<IPackageDataVisualizer> m_PackageVisualizer;
		const misColorStruct PlanColor = misColorStruct(255, 0, 0, 0);
		const std::string PlanName = "NavigationPlan";
	
	};
}
