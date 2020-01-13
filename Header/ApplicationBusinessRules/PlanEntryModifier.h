#pragma once
#include "IPlanEntryModifier.h"

#include "misCoordinateSystemCorrelationTreeManager.h"
#include "INavigationViewersNView.h"

namespace parcast
{

	class PlanEntryModifier : public IPlanEntryModifier
	{
	public:
		PlanEntryModifier(std::weak_ptr<ICoordinateSystemCorrelationManager<std::string> const> correlationMgr,
		                           std::weak_ptr<INavigationViewersNView> groupViwer);
		void ModifyPlanEntryPoint(std::weak_ptr< parcast::IPackagePlanRel> planRel, const std::string& imageUid, const std::string& toolTipUid) override;

	private:
		std::weak_ptr<ICoordinateSystemCorrelationManager<std::string> const> m_CorrelationManager;
		std::weak_ptr<INavigationViewersNView> m_GroupViwer;
	};

}
