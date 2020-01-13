#pragma once

#include "BusinessEntities\Point.h"

namespace parcast
{

	// Converts the plan data from the transform-length representation to/from start-end point. The transform created in this 
	// manner must transform a vector in the plan coordinate system to its equivalent vector in the parent coordinate system.
	// The plan coordinate system has its Z axis lying on the direction from start point to end point.
	class IPlanTransformCalculator
	{
	public:
		struct Points
		{
			Point<double, 3> Start, End;
		};

		struct TransformAndLength
		{
			double PlanLength;
			std::vector<double> CoordSysTransform;
		};

		virtual TransformAndLength FromPlanPointsWithStartTranslation(const Point<double, 3>& start, const Point<double, 3>& end) const = 0;
		virtual TransformAndLength FromPlanPointsWithEndTranslation(const Point<double, 3>& start, const Point<double, 3>& end) const = 0;
		virtual Points FromTransform(const std::vector<double>& coordSysTransform, double planLength) const = 0;

		virtual ~IPlanTransformCalculator() = default;
	};

}