#pragma once
#include "IPackageDataRenderingAdapter.h"
#include "IGroupViewerSetting.h"

class IUpdateViewPortToOblique
{
public:
	virtual ~IUpdateViewPortToOblique() = default;
	virtual void Update(std::shared_ptr<IGroupViewerSetting> viewSetting,
		std::vector<std::shared_ptr<IPackageDataRenderingAdapter>> adaptors) = 0;
};
