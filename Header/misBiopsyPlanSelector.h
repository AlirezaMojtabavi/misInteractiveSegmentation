#pragma once
#include "IPlanSelector.h"
#include "IScrewPlanView.h"
#include "IPackageDataVisualizer.h"
#include "IVolumeCropping.h"
#include "IBiopsyPlanningUIUpdater.h"

class misBiopsyPlanSelector :
	public IPlanSelector
{
public:
	misBiopsyPlanSelector(std::shared_ptr<IPackageDataVisualizer> packageDataVisualizer, 
	std::shared_ptr<INavigationViewersNView> navigationViewers, 
	std::shared_ptr<parcast::IScrewPlanView> screwPlanView,
	std::shared_ptr<IVolumeCropping> volumeCropping, std::shared_ptr<IBiopsyPlanningUIUpdater> biopsyPlanningUiUpdater);
 	void SelectPlan(std::shared_ptr<ISimpleDataPackage> package, std::weak_ptr<parcast::IPlan> plan) override;
private:
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<INavigationViewersNView> m_PlanningViewers;
	std::shared_ptr<parcast::IScrewPlanView> m_ScrewPlanView;
	std::shared_ptr<IVolumeCropping> m_VolumeCropping;
	std::shared_ptr<IBiopsyPlanningUIUpdater> m_UIUpdater;


};

