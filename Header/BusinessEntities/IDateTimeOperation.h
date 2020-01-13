#pragma once

#include "DateTime.h"

namespace  parcast
{

	class IDateTimeOperation
	{
	public:
		// string format must compatible with this : "YYYY-MM-DD HH:MM:SS"
		virtual DateTime FromString(const std::string& dateTimeStr) const = 0;
		
		// return string format : "YYYY-MM-DD HH:MM:SS"
		virtual std::string ToString(const DateTime& dateTime) const = 0;
		
		virtual DateTime FromEpoch(std::time_t timeSinceEpoch) const = 0;
		virtual std::time_t ToEpoch(const DateTime& dateTime) const = 0;
			
		virtual DateTime DecodeInt64(long long int encodedTime) const = 0;
		virtual long long int EncodeInt64(const DateTime& dateTime) const = 0;
	
		virtual ~IDateTimeOperation() = default;
	};

}