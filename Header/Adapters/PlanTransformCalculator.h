#pragma once

#include "IPlanTransformCalculator.h"

namespace parcast
{

	class PlanTransformCalculator : public IPlanTransformCalculator
	{
	public:
		TransformAndLength FromPlanPointsWithStartTranslation(const Point<double, 3>& start, const Point<double, 3>& end) const override;
		Points FromTransform(const std::vector<double>& coordSysTransform, double planLength) const override;
		TransformAndLength FromPlanPointsWithEndTranslation(const Point<double, 3>& start,
			const Point<double, 3>& end) const override;
	};


}
