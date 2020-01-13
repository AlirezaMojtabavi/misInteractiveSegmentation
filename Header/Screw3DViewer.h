#pragma once

#include "misVolumeRendererContainer.h"
#include "IInitializeScrewWidget.h"
#include "ScrewViewer.h"


class Screw3DViewer : public ScrewViewer
{
public:
	using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;
	Screw3DViewer(std::shared_ptr<IInitializeScrewWidget> initializeScrewWidget,
	              std::shared_ptr<ScrewListType> screwServiceList,
	              std::shared_ptr<ICornerProperties> cornerproperties,
	              misVolumeRendererContainer::Pointer parent);

	void InitializeScrewWidget(misScrewWidgetData initVals, IMAGEORIENTATION orientation) override;
 
};
