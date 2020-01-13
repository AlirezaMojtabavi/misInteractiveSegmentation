#pragma once
#include "IVertebraScrewPlanDataIterator.h"
#include "IPackageDataVisualizer.h"

class misVertebraScrewPlanDataIterator :
	public IVertebraScrewPlanDataIterator
{
public:
	misVertebraScrewPlanDataIterator(std::shared_ptr<IPackageDataVisualizer> packageVisualizer);
	void DoForSelectedVertebraScrewPlan(std::function<void(std::weak_ptr<misVertebraScrewPlanData>)> toDo,
		std::shared_ptr<ISimpleDataPackage> package) override;
private:
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;

};

