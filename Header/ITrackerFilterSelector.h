#pragma once

namespace parcast
{

	class ITrackerFilterSelector
	{
	public:
		virtual void Default() = 0;
		virtual void Select(int filterIndex) = 0;
		virtual void RefreshFilters() = 0;
		virtual int GetNumberOfFilters() const = 0;

		virtual ~ITrackerFilterSelector() = default;
	};

}
