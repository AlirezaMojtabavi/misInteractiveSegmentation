#pragma once
#include "IPlan.h"

namespace parcast
{

	class IPositionInPlanCoordinateSystemCalculatorSetter
	{

	public:
		virtual ~IPositionInPlanCoordinateSystemCalculatorSetter() = default;

		virtual void SetPlan(std::weak_ptr<IPlan> plan) = 0;
		virtual void SetToolTipCoordinateSystem(const std::string& toolTipCoordSys) = 0;
	};

}
