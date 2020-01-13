#include "stdafx.h"
#include "..\Header\misWidgetConfigure.h"
#include "misVolumeSlicer.h"


misWidgetConfigure::misWidgetConfigure(std::shared_ptr<IVolumeRenderer> viewer)
:m_viewer(viewer)
{
}


void misWidgetConfigure::PlaceWidgetatCenter(misPlaneEnum planeIndex, std::shared_ptr<IImage>  pMisImage)
{
	auto pos = pMisImage->GetImageCenter();
	auto GeneralRep = m_viewer->GetMainRepresentation();
	if (GeneralRep)
	{
		auto gpu2DRep = std::dynamic_pointer_cast<misPlanarRepresentation>(GeneralRep);
		if (!gpu2DRep)
			return;
		if (planeIndex == FirstImage)
		{
			auto imageView = std::dynamic_pointer_cast<misVolumeSlicer>(m_viewer);
			if (imageView)
			{
				imageView->GetCornerProperties()->SetCurrentPosition(pos.Elements());
				imageView->UpdateImage(true);
			}
		}

		if (planeIndex == SecondImage)
		{
			gpu2DRep->UpdateCorrelated();
			m_viewer->Get3DViewer()->UpdateRepresentationActors();
		}
	}
}

