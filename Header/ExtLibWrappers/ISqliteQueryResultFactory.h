#pragma once

#include "IQueryResult.h"

namespace parcast
{

	class ISqliteQueryResultFactory
	{
	public:
		virtual std::shared_ptr<IQueryResult> CreateQueryResult(sqlite3_stmt *stmt) = 0;

		virtual ~ISqliteQueryResultFactory() { }
	};

}