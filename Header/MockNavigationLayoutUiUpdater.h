#pragma once
#include "INavigationLayoutUiUpdater.h"

MOCK_BASE_CLASS(MockNavigationLayoutUiUpdater, INavigationLayoutUiUpdater)
{
	MOCK_NON_CONST_METHOD(UpdateLayout, 1, void (const misWindowsLayout&) );
	MOCK_NON_CONST_METHOD(ClearLayout, 0, void () );
};
