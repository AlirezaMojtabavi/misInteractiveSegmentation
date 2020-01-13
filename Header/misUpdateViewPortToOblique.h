#pragma once
#include "IUpdateViewPortToOblique.h"

class misUpdateViewPortToOblique : public IUpdateViewPortToOblique
{
public:
	void Update(std::shared_ptr<IGroupViewerSetting> viewSetting,
		std::vector<std::shared_ptr<IPackageDataRenderingAdapter>> adaptors) override;
};

