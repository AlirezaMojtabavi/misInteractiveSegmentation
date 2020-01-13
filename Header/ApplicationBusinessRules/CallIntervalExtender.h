#pragma once
#include "ICallIntervalExtender.h"
#include "IClock.h"

namespace parcast
{

	class CallIntervalExtender : public ICallIntervalExtender
	{
	public:
		CallIntervalExtender(std::shared_ptr<IClock const> clock, std::chrono::milliseconds const& interval);
		void Trigge(const std::function<void()>& functionObj) override;

	private:
		const std::chrono::milliseconds Interval;
		const std::shared_ptr<IClock const> Clock;

		std::chrono::milliseconds m_LastCallTime;
	};

}