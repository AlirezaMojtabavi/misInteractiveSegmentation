#pragma once

#include "IDatabaseTransactionQueryBuilder.h"
#include "IDataBaseCommandFactory.h"

namespace parcast
{

	class SqliteDatabaseTransactionQueryBuilder : public IDatabaseTransactionQueryBuilder
	{
	public:
		SqliteDatabaseTransactionQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);
		std::shared_ptr<IDataBaseCommand> GetBeginQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetCommitQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetRollBackQuery() const override;
	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;

	};

}