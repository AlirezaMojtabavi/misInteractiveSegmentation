#include "stdafx.h"
#include "ScrewViewerFactory.h"
#include "Screw2DViewer.h"
#include "Screw3DViewer.h"

std::shared_ptr<IScrewViewer> ScrewViewerFactory::Create(enum::Dimention dimention,
                                                         std::shared_ptr<IInitializeScrewWidget> initializeScrewWidget,
                                                         std::shared_ptr<ScrewListType> screwServiceList,
                                                         std::shared_ptr<ICornerProperties> cornerproperties,
                                                         misVolumeRendererContainer::Pointer parent)
{
	std::shared_ptr<IScrewViewer> screwViewer;
	switch (dimention)
	{
	case _2D:
		screwViewer = std::make_shared<Screw2DViewer>(initializeScrewWidget, screwServiceList,
		                                                       cornerproperties, parent);
		break;
	case _3D:
		screwViewer = std::make_shared<Screw3DViewer>(initializeScrewWidget, screwServiceList,
		                                                       cornerproperties, parent);
		break;
	default:
		screwViewer = std::make_shared<Screw2DViewer>(initializeScrewWidget, screwServiceList,
		                                                       cornerproperties, parent);
		break;
	}
	return screwViewer;
}
