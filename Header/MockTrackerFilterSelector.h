#pragma once

#include "ITrackerFilterSelector.h"

MOCK_BASE_CLASS(MockTrackerFilterSelector, ITrackerFilterSelector)
{
	MOCK_NON_CONST_METHOD(Default, 0, void());
	MOCK_NON_CONST_METHOD(Select, 1, void(int filterIndex));
	MOCK_NON_CONST_METHOD(Select, 1, void(int filterIndex));
	MOCK_CONST_METHOD(RefreshFilters, 0, void ());
};