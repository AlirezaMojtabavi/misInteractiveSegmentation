#pragma once

#include "IAvailabilityChangedObserver.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockAvailabilityChangedObserver, IAvailabilityChangedObserver)
	{
		MOCK_NON_CONST_METHOD(CurrentAvailabilityChanged, 0, void());
	};

}