#pragma once
#include "IPlanSelector.h"
#include "misVertebraScrewPlanData.h"
#include "ISimpleDataPackage.h"
#include "INavigationViewersNView.h"
#include "IPackageDataVisualizer.h"
#include "IScrewPlanView.h"

class misScrewPlanSelector : public IPlanSelector
{
public:
	misScrewPlanSelector(std::shared_ptr<IPackageDataVisualizer> , std::shared_ptr<INavigationViewersNView>,
	                std::shared_ptr<parcast::IScrewPlanView> screwPlanView);
	
	void SelectPlan(std::shared_ptr<ISimpleDataPackage> package, std::weak_ptr<parcast::IPlan> plan) override;
private:
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<INavigationViewersNView> m_PlanningViewers;
	std::shared_ptr<parcast::IScrewPlanView> m_ScrewPlanView;


};

