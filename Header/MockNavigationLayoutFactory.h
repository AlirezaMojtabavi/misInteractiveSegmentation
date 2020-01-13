#pragma once
#include "INavigationLayoutFactory.h"

MOCK_BASE_CLASS(MockNavigationLayoutFactory, INavigationLayoutFactory)
{
	MOCK_CONST_METHOD(GetLayout, 0, std::shared_ptr<IGroupViewerSetting>());
	MOCK_CONST_METHOD(GetLayoutFromFile, 1, std::shared_ptr<IGroupViewerSetting>(const std::string& file));
};
