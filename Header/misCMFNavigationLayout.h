#pragma once

#include "INavigationLayoutFactory.h"


class misCMFNavigationLayout : public INavigationLayoutFactory
{
public:
	std::shared_ptr<IGroupViewerSetting> GetLayout() const override;
	std::shared_ptr<IGroupViewerSetting> GetLayoutFromFile(const std::string& layoutName) const override;
};
