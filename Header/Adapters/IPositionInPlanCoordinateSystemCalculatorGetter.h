#pragma once
#include "BusinessEntities\Point.h"
#include "ITransform.h"

namespace parcast
{

	class IPositionInPlanCoordinateSystemCalculatorGetter
	{

	public:
		virtual ~IPositionInPlanCoordinateSystemCalculatorGetter() = default;

		virtual PointD3 GetToolTip() const = 0;
		virtual PointD3 GetPredictedTarget() const = 0;
		virtual std::shared_ptr<const ITransform> GetImageToPlanTransform() const = 0;
		virtual bool IsToolValid() const = 0;
	};

}
