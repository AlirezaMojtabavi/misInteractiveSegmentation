#include "stdafx.h"
#include "misUpdateViewPortToStandard.h"
#include "IPackageDataRenderingAdapter.h"
#include "misViewPort.h"
#include "IVolume3DRenderer.h"
#include "I3DViewer.h"


misUpdateViewPortToStandard::misUpdateViewPortToStandard()
{
}


misUpdateViewPortToStandard::~misUpdateViewPortToStandard()
{
}

void misUpdateViewPortToStandard::Update(std::vector<std::shared_ptr<IPackageDataRenderingAdapter>> viewers,
                                       std::shared_ptr<IGroupViewerSetting> groupViewSetting)
{
	auto  viewerIndex = 0;
	for (int i = 0; i < groupViewSetting->GetNumberOfGroupElement(); i++)
	{
		const auto group = groupViewSetting->GetElement(i);
		const auto numberOfViewerInGroup = group.GetNumberOfViewer();
		if (numberOfViewerInGroup == 1)
		{
			viewerIndex++;
			continue;
		}

		viewers[viewerIndex]->GetViewer()->SetViewPort(misViewPort(tgt::Vector2d(0, 0), tgt::Vector2d(1, 1)));
		for (int j = viewerIndex + 1; j < viewerIndex + numberOfViewerInGroup; j++)
		{
			viewers[j]->GetViewer()->SetViewPort(misViewPort(tgt::Vector2d(1, 1), tgt::Vector2d(0, 0)));
		}

		viewerIndex += numberOfViewerInGroup;
	}
}
