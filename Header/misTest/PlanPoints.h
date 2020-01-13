#pragma once
#include "BusinessEntities/Point.h"

namespace parcast
{
	class PlanPoints
	{
	public:
		PlanPoints(parcast::Point<double, 3> start, parcast::Point<double, 3> end) : m_Start(start), m_End(end)
		{
		}

		double GetLength() const
		{
			return (m_Start - m_End).Length();
		}

		auto GetStart() const
		{
			return m_Start;
		}

		auto GetEnd() const
		{
			return m_End;
		}
	private:
		parcast::Point<double, 3> m_Start;
		parcast::Point<double, 3> m_End;

	};
}
