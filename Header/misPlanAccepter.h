#pragma once
#include "INavigationViewersNView.h"
#include "IPlanAccepter.h"
#include "IScrewPlanView.h"

class misPlanAccepter : public IPlanAccepter
{
public:
	misPlanAccepter(std::shared_ptr<INavigationViewersNView> groupViewer, std::shared_ptr<IScrewPlanView> screwView) ;
	void AcceptPlan(std::weak_ptr<parcast::IPlan> plan, const ScrewPlanInformation& planInfo) override;
private:
	std::shared_ptr<INavigationViewersNView> m_PlanningViewers;
	std::shared_ptr<IScrewPlanView> m_ScrewPlanView;
};

