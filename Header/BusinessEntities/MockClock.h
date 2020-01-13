#pragma once

#include "IClock.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockClock, IClock)
	{
		MOCK_CONST_METHOD(GetCurrentTime, 0, DateTime());
		MOCK_CONST_METHOD(GetSecondsFromEpoch, 0, std::time_t());
		MOCK_CONST_METHOD(GetMillisecondsFromEpoch, 0, std::chrono::milliseconds());
	};

}