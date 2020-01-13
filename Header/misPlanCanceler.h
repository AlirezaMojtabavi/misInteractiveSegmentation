#pragma once
#include "INavigationViewersNView.h"
#include "IDatasetManager.h"
#include "IPlanningHelperUIUpdater.h"
#include "IPlanCanceler.h"
#include "IPlanRepo.h"
#include "IScrewPlanView.h"

class misPlanCanceler : public IPlanCanceler
{
public:
	misPlanCanceler(std::shared_ptr<INavigationViewersNView> planningViewer, IDatasetManager*,
	                std::shared_ptr<IPlanningHelperUIUpdater> uiUpdater, std::shared_ptr<parcast::IPlanRepo> planRepo, std::shared_ptr<IScrewPlanView> screwView);
	void CancelPlan(std::shared_ptr<ISimpleDataPackage> package,
	                std::weak_ptr<parcast::IPlan> currentPlan) override;
private:
	std::shared_ptr<INavigationViewersNView> m_PlanningViewers;
	IDatasetManager* m_DatasetManager;
	std::shared_ptr<IPlanningHelperUIUpdater> m_UiUpdater;
	std::shared_ptr<parcast::IPlanRepo> m_PlanRepo;
	std::shared_ptr<IScrewPlanView> m_ScrewPlanView;
};
