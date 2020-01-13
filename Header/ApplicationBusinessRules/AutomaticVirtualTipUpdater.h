#pragma once

#include "IAutomaticVirtualTipUpdater.h"
#include "IENTNavigationUIUpdater.h"
#include "IVirtualTipLengthCalculator.h"
#include "IBiopsyNavigationUiUpdater.h"

namespace parcast
{
	class AutomaticVirtualTipUpdater : public IAutomaticVirtualTipUpdater
	{
	public:
		AutomaticVirtualTipUpdater(
			std::weak_ptr<IBiopsyNavigationUiUpdater> uiUpdater,
			std::unique_ptr<IVirtualTipLengthCalculator> virtualTipLengthCalculator);

		void SetEnabled(bool isAutomaticMode) override;
		void Update(std::weak_ptr<const ITransform> toolTransform, parcast::PointD3 const& targetPos,
			double const& targetRadius)  override;
		boost::optional<double> GetLength() const override;
	private:
		std::weak_ptr<IBiopsyNavigationUiUpdater> m_UiUpdater;
		std::unique_ptr<IVirtualTipLengthCalculator> m_LengthCalculator;
		bool m_IsEnabled = false;
		boost::optional<double> m_Lenght;
	};

}
