#pragma once
#include "Adapters/IPositionInPlanCoordinateSystemCalculatorGetter.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPositionInPlanCoordinateSystemCalculatorGetter, IPositionInPlanCoordinateSystemCalculatorGetter)
	{
		MOCK_CONST_METHOD(GetToolTip, 0, PointD3());
		MOCK_CONST_METHOD(GetPredictedTarget, 0, PointD3());
		MOCK_CONST_METHOD(GetImageToPlanTransform, 0, std::shared_ptr<const ITransform>());
		MOCK_CONST_METHOD(IsToolValid, 0, bool());
	};

}
