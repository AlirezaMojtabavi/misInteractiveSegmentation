#pragma once

#include "IPackageDataVisualizer.h"

namespace parcast
{
	class IPlanCreator
	{
	public:
		virtual ~IPlanCreator() = default;
		virtual std::shared_ptr<IPlan> CreatePlan(const misUID imageUid, std::shared_ptr<ISimpleDataPackage> currentPkg) = 0;
	};
}
