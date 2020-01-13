#pragma once

#include "FloatingPointCompare.h"
#include "PlanIndicators.h"

namespace parcast
{

	class PlanIndicatorsMatcher
	{
	public:
		PlanIndicatorsMatcher(const PlanIndicators& expected, double tolerance = 1e-6)
			: m_Expected(expected),
			Tolerance(tolerance)
		{
		}

		bool operator()(const PlanIndicators& received)
		{
			return FloatingPointCompare::IsClose(received.PlanCentricViewAngle, m_Expected.PlanCentricViewAngle, Tolerance) &&
				FloatingPointCompare::IsClose(received.PlanDiameter, m_Expected.PlanDiameter, Tolerance) &&
				received.Visibility == m_Expected.Visibility;
		}

	private:
		PlanIndicators m_Expected;
		double Tolerance;
	};

}