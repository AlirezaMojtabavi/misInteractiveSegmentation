#pragma once
#include "IScrewPlanDeleter.h"
#include "IPlanCanceler.h"
#include "INavigationViewersNView.h"
#include "IScrewPlanView.h"

namespace parcast
{
	class ScrewPlanDeleter :
		public parcast::IScrewPlanDeleter
	{
	public:
		ScrewPlanDeleter(std::shared_ptr<IPlanCanceler> planCanceler, std::shared_ptr<INavigationViewersNView> planningViewers, 
			std::shared_ptr<parcast::IScrewPlanView> );
		bool DeleteCurrentPlan(bool& modifyingPlanMode, 
			std::shared_ptr<ISimpleDataPackage>, 
			std::shared_ptr<parcast::IPlan> planUnderEdit,
			std::weak_ptr<parcast::IPlan> currentlySelectedPlan
			) override;
	private:
		std::shared_ptr<IPlanCanceler> m_PlanCanceler;
		std::shared_ptr<INavigationViewersNView> m_PlanningViewers;
		std::shared_ptr<parcast::IScrewPlanView> m_ScrewPlanView;
	};
}

