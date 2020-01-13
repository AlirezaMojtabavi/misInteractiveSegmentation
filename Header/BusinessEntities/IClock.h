#pragma once

#include "DateTime.h"

// Some stupid Windows header might have #define'd the name GetCurrentTime
#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

namespace parcast
{

	// The IClock class provides the abstract interface to services provided by a clock (system clock e.g.)
	class IClock
	{
	public:
		virtual DateTime GetCurrentTime() const = 0;
		virtual std::time_t GetSecondsFromEpoch() const = 0;
		virtual std::chrono::milliseconds GetMillisecondsFromEpoch() const = 0;

		virtual ~IClock() { }
	};

}