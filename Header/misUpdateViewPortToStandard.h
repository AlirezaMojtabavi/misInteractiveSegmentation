#pragma once
#include "IUpdateViewPortToStandard.h"
#include "I3DViewer.h"

class misUpdateViewPortToStandard : public IUpdateViewPortToStandard
{
public:
	misUpdateViewPortToStandard();
	~misUpdateViewPortToStandard();
	void Update(std::vector<std::shared_ptr<IPackageDataRenderingAdapter>> viewers,
	            std::shared_ptr<IGroupViewerSetting> groupViewSetting) override;
};

