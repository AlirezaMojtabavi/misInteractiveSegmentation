#pragma once

#include "IPlanTransformCalculator.h"
namespace parcast
{
	MOCK_BASE_CLASS(MockPlanTransformCalculator, IPlanTransformCalculator)
	{
		MOCK_CONST_METHOD(FromPlanPointsWithStartTranslation, 2, TransformAndLength(const Point<double, 3>& , const Point<double, 3>& ));
		MOCK_CONST_METHOD(FromPlanPointsWithEndTranslation, 2,TransformAndLength (const Point<double, 3>& , const Point<double, 3>& ) );
		MOCK_CONST_METHOD(	FromTransform, 2, Points FromTransform(const std::vector<double>& coordSysTransform, double planLength));
	};
}