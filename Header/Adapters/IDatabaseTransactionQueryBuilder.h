#pragma once
#include "IDataBaseCommand.h"

namespace parcast
{

	class IDatabaseTransactionQueryBuilder
	{
	public:
		virtual std::shared_ptr<IDataBaseCommand> GetBeginQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetCommitQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetRollBackQuery() const = 0;

		virtual ~IDatabaseTransactionQueryBuilder() = default;
	};

}
