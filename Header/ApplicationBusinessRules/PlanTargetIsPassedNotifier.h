#pragma once
#include "IPlanTargetIsPassedNotifier.h"
#include "IBiopsyNavigationUiUpdater.h"

namespace parcast
{
	class PlanTargetIsPassedNotifier : public IPlanTargetIsPassedNotifier
	{
	public:
		explicit PlanTargetIsPassedNotifier(std::weak_ptr<IBiopsyNavigationUiUpdater> uiUpdater);
		void UpdateStatus(
			PointD3 entryPoint, PointD3 targetPoint, double targetRegionDiameter, std::shared_ptr<const ITransform>toolTransform) const override;

	private:
		std::weak_ptr<IBiopsyNavigationUiUpdater> m_UiUpdater;
	};
}
