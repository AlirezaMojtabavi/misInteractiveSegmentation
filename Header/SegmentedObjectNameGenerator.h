#pragma once

#include "ISegmentedObjectNameGenerator.h"


namespace parcast
{
	class SegmentedObjectNameGenerator : public ISegmentedObjectNameGenerator
	{
	public:

		virtual std::string GetName(mis3DModelTypes type) override;

	};
}