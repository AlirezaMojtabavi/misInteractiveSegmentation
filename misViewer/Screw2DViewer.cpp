#include "stdafx.h"
#include "Screw2DViewer.h"
#include "misVolumeSlicer.h"
#include "misPlanWidget.h"
#include <misMemberCommandCallback.h>


Screw2DViewer::Screw2DViewer(std::shared_ptr<IInitializeScrewWidget> initializeScrewWidget,
                                      std::shared_ptr<ScrewListType> screwServiceList,
                                      std::shared_ptr<ICornerProperties> cornerproperties,
                                      misVolumeRendererContainer::Pointer parent):
	ScrewViewer(std::move(initializeScrewWidget), screwServiceList, cornerproperties, parent)
{
}

void Screw2DViewer::InitializeScrewWidget(misScrewWidgetData initVals, IMAGEORIENTATION orientation)
{
	auto screwCompound = m_InitializeScrewWidget->Initialize(initVals, orientation);
	if (screwCompound)
	{
		auto screwWidgetCallback = misMemberCommandCallback<ScrewViewer>::New();
		screwWidgetCallback->SetCallbackFunction(this, &ScrewViewer::UpdateScrewWidget);
		if (!screwCompound->GetWidget()->HasObserver(vtkCommand::EndInteractionEvent))
			screwCompound->GetWidget()->AddObserver(vtkCommand::EndInteractionEvent, screwWidgetCallback);
	}
}