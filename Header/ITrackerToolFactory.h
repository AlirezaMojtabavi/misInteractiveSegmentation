#pragma once
#include <igstkTrackerTool.h>
#include "misTrackingManagerEnums.h"

namespace parcast
{

	class ITrackerToolFactory
	{
	public:
		virtual igstk::TrackerTool::Pointer Create(const std::string& toolUid, TrackerType trackerType) = 0;
	};

}
