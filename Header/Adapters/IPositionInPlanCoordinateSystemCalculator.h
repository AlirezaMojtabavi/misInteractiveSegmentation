#pragma once
#include "Point.h"
#include "IDentalPlan.h"

namespace parcast
{

	class IPositionInPlanCoordinateSystemCalculator
	{

	public:
		virtual PointD3 GetToolTip() const = 0;
		virtual PointD3 GetPredictedToolTip() const = 0;
		virtual void SetPlan(std::weak_ptr<IDentalPlan> plan) = 0;
		virtual void SetToolTipCoordinateSystem(const std::string& toolTipCoordSys) = 0;
	};

}
