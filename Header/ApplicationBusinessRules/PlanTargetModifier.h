#pragma once
#include "IPlanTargetModifier.h"
#include "INavigationViewersNView.h"

namespace parcast
{

	class PlanTargetModifier : public IPlanTargetModifier
	{
	public:
		PlanTargetModifier(
			std::weak_ptr<ICoordinateSystemCorrelationManager<std::string> const> correlationMgr,
			std::weak_ptr<INavigationViewersNView> groupViwer);

		void ModifyPlanTargetPoint(std::weak_ptr<parcast::IPackagePlanRel> planRel, const std::string& imageUid,
		                           const std::string& toolTipUid) override;

		void SetVirtualTipLength(double length) override;;

	private:
		std::weak_ptr<ICoordinateSystemCorrelationManager<std::string> const> m_CorrelationManager;
		std::weak_ptr<INavigationViewersNView> m_GroupViwer;
		double m_VirtualTipLenght = 0.0;
	};

}
