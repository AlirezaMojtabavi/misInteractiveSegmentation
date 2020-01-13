#pragma once
#include "IGroupViewerSettingFinder.h"

MOCK_BASE_CLASS(MockGroupViewerSettingFinder, IGroupViewerSettingFinder)
{
	MOCK_NON_CONST_METHOD(MakePckageGroupViewer, 1,  std::shared_ptr<IGroupViewerSetting> (std::string ) );

};
