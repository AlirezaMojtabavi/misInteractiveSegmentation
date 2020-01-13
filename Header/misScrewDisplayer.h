#pragma once
#include "IScrewPlanDisplayer.h"
#include "ISimpleDataPackage.h"
#include "IPackageDataVisualizer.h"
#include "IPlanningHelperUIUpdater.h"
#include "IVertebraScrewPlanDataIterator.h"
#include "IScrewPlanView.h"

class misScrewDisplayer :
	public IScrewDisplayer
{
public:
	misScrewDisplayer(std::shared_ptr<IPackageDataVisualizer> packgeVisualizer,
	                  std::shared_ptr<INavigationViewersNView> planningViewers,
	                  std::shared_ptr<IPlanningHelperUIUpdater> uIUpdater,
		std::shared_ptr<IVertebraScrewPlanDataIterator> screwIterator,
		std::shared_ptr<IScrewPlanView> screwView
	);
	~misScrewDisplayer();
	void ShowScrews(std::shared_ptr<ISimpleDataPackage> package) override;
private:
	void UpdatePlanPropertyIndicatorInGUI(std::shared_ptr<ISimpleDataPackage> package);
	
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<INavigationViewersNView> m_PlanningViewers;
	std::shared_ptr<IPlanningHelperUIUpdater> m_UIUpdater;
	std::shared_ptr<IVertebraScrewPlanDataIterator> m_ScrewIterator;
	std::shared_ptr<IScrewPlanView> m_ScrewPlanView;

};

