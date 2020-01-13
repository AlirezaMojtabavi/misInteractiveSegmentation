#pragma once
#include "IBiopsyAcceptPlan.h"
#include "BiopsyPlanningFlow.h"
#include "IScrewPlanView.h"

namespace parcast
{
	class BiopsyAcceptPlan :
		public IBiopsyAcceptPlan
	{
	public:
		BiopsyAcceptPlan(std::shared_ptr<IBiopsyPlanningFlow> biopsyPlanningFlow, std::shared_ptr<INavigationViewersNView> , std::shared_ptr<parcast::IScrewPlanView>);
		bool AcceptPlan(const BiopsyPlanInformation& planInformation, std::shared_ptr<ISimpleDataPackage>, std::shared_ptr<parcast::IPlan>
		                currentlySelectedPlan) override;
	private:
		std::shared_ptr<IBiopsyPlanningFlow> m_BiopsyPlanningFlow;
		std::shared_ptr<INavigationViewersNView> m_GroupViewer;
		std::shared_ptr<parcast::IScrewPlanView> m_ScrewPlanView;

	};

	
}
