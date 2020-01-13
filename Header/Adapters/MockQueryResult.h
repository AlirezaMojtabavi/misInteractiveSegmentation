#pragma once

#include "IQueryResult.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockQueryResult, IQueryResult)
	{
		MOCK_NON_CONST_METHOD(Next, 0, void());
		MOCK_NON_CONST_METHOD(HasData, 0, bool());
		MOCK_NON_CONST_METHOD(GetString, 1, std::string(int colIndex));
		MOCK_NON_CONST_METHOD(GetInt, 1, long long int(int colIndex));
		MOCK_NON_CONST_METHOD(GetDouble, 1, double(int colIndex));
		MOCK_NON_CONST_METHOD(GetBool, 1, bool(int colIndex));
		MOCK_NON_CONST_METHOD(GetDateTime, 1, parcast::DateTime(int colIndex));
		MOCK_NON_CONST_METHOD(GetBinary, 1, std::shared_ptr<ByteArray>(int colIndex));
	};

}
