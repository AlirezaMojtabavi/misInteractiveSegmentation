#pragma once

#include "IClock.h"
#include "DateTime.h"

namespace parcast
{

	class Clock : public IClock
	{
	public:
		DateTime GetCurrentTime() const override;
		std::time_t GetSecondsFromEpoch() const override;
		std::chrono::milliseconds GetMillisecondsFromEpoch() const override;
	};

}