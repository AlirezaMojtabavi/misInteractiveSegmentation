#pragma once
#include "ITrackerToolFactory.h"

namespace parcast
{

	class TrackerToolFactory : public ITrackerToolFactory
	{
	public:
		igstk::TrackerTool::Pointer Create(const std::string& toolUid, TrackerType trackerType) override;
	};

}