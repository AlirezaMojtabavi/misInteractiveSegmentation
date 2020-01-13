#pragma once

#include "DateTime.h"

struct misDateTime
{
	misDateTime (const parcast::DateTime& other)
		: Year(other.GetYear()),
		Month(other.GetMonth()),
		Day(other.GetDay()),
		Hour(other.GetHour()),
		Minute(other.GetMinute()),
		Second(static_cast<int>(other.GetSecond()))
	{
	}

	explicit operator parcast::DateTime() const
	{
		return parcast::DateTime(Year , Month , Day, Hour, Minute, Second);
	}

	int Year;
	int Month;
	int Day;
	int Hour;
	int Minute;
	int Second;

	misDateTime()
	{
		this->Reset();
	}

	void Reset()
	{
		Hour = 0 ;
		Minute = 0 ;
		Second = 0 ;
		Year = 0 ;
		Month = 0 ;
		Day = 0 ;
	};
	
	bool empty()
	{
		bool returnValue = false;

		if(Hour == 0 && Minute == 0 && Second == 0 && Year == 0 && Month == 0 && Day == 0)
			returnValue = true;

		return returnValue;
	}

};




