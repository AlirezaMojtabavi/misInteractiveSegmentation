#pragma once
#include "IScrewCreator.h"
#include "IPlanRepo.h"
#include "ISimpleDataPackage.h"
#include "IDatasetManager.h"
#include "misVertebraScrewPlanData.h"
#include "IPackageDataVisualizer.h"

class misScrewCreator : public IScrewCreator
{
public:

	misScrewCreator(std::shared_ptr<parcast::IPlanRepo> planRepo, 
	                IDatasetManager*, std::shared_ptr<IPackageDataVisualizer> packageVisualizer);
	std::weak_ptr<parcast::IPlan> CreateScrew(std::shared_ptr<ISimpleDataPackage> package, const misColorStruct& color, double screwDiameter) override;
private:
	std::weak_ptr<parcast::IPlanRepo> m_PlanRepo;
	IDatasetManager* m_DataSetManger;
	std::weak_ptr<IPackageDataVisualizer> m_PackageVisualizer;

};


