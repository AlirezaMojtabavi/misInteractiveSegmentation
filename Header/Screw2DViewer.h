#pragma once
#include "IInitializeScrewWidget.h"
#include "ICornerProperties.h"
#include "misVolumeRendererContainer.h"
#include "ScrewViewer.h"


class Screw2DViewer : public ScrewViewer
{
public:
	using ScrewListType = std::vector<std::shared_ptr<IScrewCompound>>;
	Screw2DViewer(std::shared_ptr<IInitializeScrewWidget> initializeScrewWidget,
	              std::shared_ptr<ScrewListType> screwServiceList,
	              std::shared_ptr<ICornerProperties> cornerproperties,
	              misVolumeRendererContainer::Pointer parent);

	void InitializeScrewWidget(misScrewWidgetData initVals, IMAGEORIENTATION orientation) override;
};
