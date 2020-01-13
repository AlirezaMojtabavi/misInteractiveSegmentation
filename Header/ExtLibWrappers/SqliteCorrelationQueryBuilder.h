#pragma once

#include "ICorrelationQueryBuilder.h"
#include "IDataBaseCommandFactory.h"

namespace parcast
{

	class SqliteCorrelationQueryBuilder : public ICorrelationQueryBuilder
	{
	public:
		SqliteCorrelationQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		virtual std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectBySolutionUidQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteBySolutionUidQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteBySourceUidQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteByDestinationUidQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteAllQuery() const override;

	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}

