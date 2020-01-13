#pragma once
#include "IImageCorrelationSynchronizer.h"
#include "INavigationViewersNView.h"

namespace parcast
{

	class ImageCorrelationSynchronizer : public IImageCorrelationSynchronizer
	{
	public:
		ImageCorrelationSynchronizer(std::shared_ptr<INavigationViewersNView> groupViewer);
		void SyncFixedImageWithMovingImage(bool val) override;

	private:
		std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	};

}
