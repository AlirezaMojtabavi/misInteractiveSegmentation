#pragma once

namespace parcast
{

	// The DateTime is a simple structure used for holding a decomposed date/time. It does and should not provide any date/time
	// computation operations and/or date/time validations as these would be locale-specific. This structure holds date/time 
	// data in locale-agnostic manner. Furthermore date/time operations and validation would also require unit testing and 
	// interface segregation which is beyond the scope of basic data type definition.
	class DateTime
	{
	public:
		DateTime();
		DateTime(int year, unsigned char month, unsigned char day);
		DateTime(int year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute, double second);

		int GetYear() const;
		int GetMonth() const;
		int GetDay() const;
		int GetHour() const;
		int GetMinute() const;
		double GetSecond() const;

	private:
		int m_Year;
		unsigned char m_Month, m_Day, m_Hour, m_Minute;
		double m_Second;
	};

}