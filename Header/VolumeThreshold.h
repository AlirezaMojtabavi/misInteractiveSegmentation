#pragma once
#include "IVolumeThreshold.h"
#include <misEnums.h>
#include <IImage.h>
#include "ISimpleDataPackage.h"
#include "INavigationViewersNView.h"
namespace parcast
{
	class VolumeThreshold : public IVolumeThreshold
	{
	public:
		VolumeThreshold(std::shared_ptr<INavigationViewersNView> groupViewer);
		void SetVolumeThreshold(std::shared_ptr<ISimpleDataPackage> workingPackage, double threshold, misApplicationType appType, const misVisualizationSetting& visulaizationSetting) override;
	private:
 		std::shared_ptr<INavigationViewersNView> m_GroupViewer;

	};
}


