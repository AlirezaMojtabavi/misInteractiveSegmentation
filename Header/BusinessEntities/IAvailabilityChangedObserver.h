#pragma once
namespace parcast
{
	class IAvailabilityChangedObserver
	{
	public:

		virtual void CurrentAvailabilityChanged() = 0;

		virtual ~IAvailabilityChangedObserver() { }
	};
}

