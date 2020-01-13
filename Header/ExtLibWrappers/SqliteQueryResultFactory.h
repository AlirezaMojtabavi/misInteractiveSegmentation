#pragma once

#include "ISqliteQueryResultFactory.h"
#include "IDateTimeOperation.h"

namespace parcast
{

	class SqliteQueryResultFactory : public ISqliteQueryResultFactory
	{
	public:
		SqliteQueryResultFactory(const std::shared_ptr<IDateTimeOperation> dateTimeOpes);

		virtual std::shared_ptr<IQueryResult> CreateQueryResult(sqlite3_stmt * stmt) override;

	private:
		std::shared_ptr<IDateTimeOperation> m_DateTimeOperation;
	};

}


