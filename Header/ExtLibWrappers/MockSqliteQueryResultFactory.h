#pragma once

#include "ISqliteQueryResultFactory.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockSqliteQueryResultFactory, ISqliteQueryResultFactory)
	{
		MOCK_NON_CONST_METHOD(CreateQueryResult, 1, std::shared_ptr<IQueryResult>(sqlite3_stmt * stmt));
	};

}



