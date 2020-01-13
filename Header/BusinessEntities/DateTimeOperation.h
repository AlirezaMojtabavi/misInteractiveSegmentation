#pragma once

#include "IDateTimeOperation.h"

namespace parcast
{

	class DateTimeOperation : public IDateTimeOperation
	{
	public:
		DateTimeOperation();

		virtual DateTime FromString(const std::string& dateTimeStr) const override;
		virtual std::string ToString(const DateTime& dateTime) const override;
		virtual DateTime FromEpoch(std::time_t timeSinceEpoch) const override;
		virtual std::time_t ToEpoch(const DateTime&) const override;
		virtual DateTime DecodeInt64(long long int encodedTime) const override;
		virtual long long int EncodeInt64(const DateTime& dateTime) const override;

	private:
		union DateTimeCodec
		{
			long long int Encoded;
			struct
			{
				unsigned int m_Second : 11;
				unsigned int m_Minute : 6;
				unsigned int m_Hour : 5;
				unsigned int m_Day : 6;
				unsigned int m_Month : 4;
				int m_Year : 32;
			} m_DateTime;
		};
	};

}


