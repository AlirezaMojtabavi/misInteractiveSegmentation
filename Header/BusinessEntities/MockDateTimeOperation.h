
#pragma once
#include "IDateTimeOperation.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockDateTimeOperation, IDateTimeOperation)
	{
		MOCK_CONST_METHOD(FromString, 1, DateTime(const std::string& dateTimeStr));
		MOCK_CONST_METHOD(ToString, 1, std::string(const DateTime& dateTime));
		MOCK_CONST_METHOD(FromEpoch, 1, DateTime(std::time_t timeSinceEpoch));
		MOCK_CONST_METHOD(ToEpoch, 1, std::time_t(const DateTime&));
		MOCK_CONST_METHOD(DecodeInt64, 1, DateTime (long long int encodedTime));
		MOCK_CONST_METHOD(EncodeInt64, 1, long long int (const DateTime& dateTime));
	};

}
