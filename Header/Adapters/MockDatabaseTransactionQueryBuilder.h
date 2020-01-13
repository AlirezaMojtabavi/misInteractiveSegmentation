#pragma once

#include "IDataBaseCommand.h"
#include "IDatabaseTransactionQueryBuilder.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockDatabaseTransactionQueryBuilder, IDatabaseTransactionQueryBuilder)
	{
		MOCK_CONST_METHOD(GetBeginQuery, 0, std::shared_ptr<IDataBaseCommand> ());
		MOCK_CONST_METHOD(GetCommitQuery, 0, std::shared_ptr<IDataBaseCommand> ());
		MOCK_CONST_METHOD(GetRollBackQuery, 0, std::shared_ptr<IDataBaseCommand> ());
	};
}
