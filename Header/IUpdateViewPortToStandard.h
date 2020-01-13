#pragma once
#include "IPackageDataRenderingAdapter.h"
#include "IGroupViewerSetting.h"
#include "I3DViewer.h"

class IUpdateViewPortToStandard
{
public:
	virtual ~IUpdateViewPortToStandard() = default;
	virtual void Update(std::vector<std::shared_ptr<IPackageDataRenderingAdapter>> adapters,
	                    std::shared_ptr<IGroupViewerSetting> groupViewSetting) = 0;
};
