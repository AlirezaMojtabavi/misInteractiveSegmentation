#include "stdafx.h"
#include "misUpdateViewPortToOblique.h"
#include "IVolume3DRenderer.h"


void misUpdateViewPortToOblique::Update(std::shared_ptr<IGroupViewerSetting> viewSetting,
	std::vector<std::shared_ptr<IPackageDataRenderingAdapter>> adaptors)
{
 	int viewerIndex = 0;
	for (int i = 0; i < viewSetting->GetNumberOfGroupElement(); i++)
	{
		misViewElementGroup group = viewSetting->GetElement(i);
		int numberOfViewerInGroup = group.GetNumberOfViewer();
		if (numberOfViewerInGroup == 1)
		{
			viewerIndex++;
			continue;
		}
		int indeInGroup = 0;
		for (int j = viewerIndex; j < viewerIndex + numberOfViewerInGroup; j++)
		{
			misViewPort port = group.GetViewPort(indeInGroup);
			adaptors[j]->GetViewer()->SetViewPort(port);

			indeInGroup++;
		}

		viewerIndex += numberOfViewerInGroup;
	}

}
