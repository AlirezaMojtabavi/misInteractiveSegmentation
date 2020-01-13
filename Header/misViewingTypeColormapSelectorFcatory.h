#pragma once
#include <memory>
#include "IViewingTypeColormapSelector.h"

class misViewingTypeColormapSelectorFcatory
{
public :
	static std::unique_ptr<IViewingTypeColormapSelector> CreateVolumeSelector(misApplicationType appType,
		std::shared_ptr<INavigationViewersNView>	groupViewer);
};
