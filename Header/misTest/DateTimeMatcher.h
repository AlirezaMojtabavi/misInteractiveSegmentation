#pragma once

#include "DateTime.h"

namespace parcast
{

	class DateTimeMatcher
	{
	public:
		DateTimeMatcher(DateTime & dateTime, double tolerance = 1.0 / 17)
			: m_DateTime(dateTime), m_ToleranceSqr(tolerance * tolerance) { }

		bool operator()(const DateTime & checkDateTime) const
		{
			return IsEqual(checkDateTime, m_DateTime, m_ToleranceSqr);
		}

		static bool IsEqual(const DateTime & a, const DateTime & b, double tolerance = 1.0 / 17)
		{
			return
				a.GetYear() == b.GetYear() &&
				a.GetMonth() == b.GetMonth() &&
				a.GetDay() == b.GetDay() &&
				a.GetHour() == b.GetHour() &&
				a.GetMinute() == b.GetMinute() &&
				(a.GetSecond() - b.GetSecond()) * (a.GetSecond() - b.GetSecond()) < tolerance;
		}

	private:
		const DateTime& m_DateTime;
		const double m_ToleranceSqr;
	};

}