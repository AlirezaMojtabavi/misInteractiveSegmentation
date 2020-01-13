#pragma once

namespace parcast
{

	class ICallIntervalExtender
	{
	public:
		virtual ~ICallIntervalExtender() = default;
		virtual void Trigge(const std::function<void()>& functionObj) = 0;
	};

}