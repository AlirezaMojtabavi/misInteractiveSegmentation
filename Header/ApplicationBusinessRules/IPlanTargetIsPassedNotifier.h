#pragma once
#include "BusinessEntities\Point.h"

namespace parcast
{
	class IPlanTargetIsPassedNotifier
	{
	public:
		virtual ~IPlanTargetIsPassedNotifier() = default;
		virtual void UpdateStatus(
			PointD3 entryPoint, PointD3 targetPoint, double targetRegioRadius, std::shared_ptr<const ITransform> toolTransform) const = 0;
	};
}
