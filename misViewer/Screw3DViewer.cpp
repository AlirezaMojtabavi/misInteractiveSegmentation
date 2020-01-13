#include "stdafx.h"
#include "Screw3DViewer.h"
#include "misPlanWidget.h"
#include <misMemberCommandCallback.h>



Screw3DViewer::Screw3DViewer(std::shared_ptr<IInitializeScrewWidget> initializeScrewWidget,
                                      std::shared_ptr<ScrewListType> screwServiceList,
                                      std::shared_ptr<ICornerProperties> cornerproperties,
                                      misVolumeRendererContainer::Pointer parent)
	: ScrewViewer(std::move(initializeScrewWidget), screwServiceList, cornerproperties, parent)
{
}



void Screw3DViewer::InitializeScrewWidget(misScrewWidgetData initVals, IMAGEORIENTATION orientation)
{
	auto screwCompound = m_InitializeScrewWidget->Initialize(initVals, orientation);
	if (screwCompound)
	{
		auto screwWidgetCallback = misMemberCommandCallback<Screw3DViewer>::New();
		screwWidgetCallback->SetCallbackFunction(this, &Screw3DViewer::UpdateScrewWidget);
		if (!screwCompound->GetWidget()->HasObserver(vtkCommand::EndInteractionEvent))
			screwCompound->GetWidget()->AddObserver(vtkCommand::EndInteractionEvent, screwWidgetCallback);
	}
}
