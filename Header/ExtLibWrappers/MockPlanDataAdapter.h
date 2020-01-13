#pragma once
#include "IPlanDataAdapter.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockPlanDataAdapter, IPlanDataAdapter)
	{
		MOCK_NON_CONST_METHOD(Save, 0, void());
		MOCK_NON_CONST_METHOD(Load, 0, void());
	};
}