#pragma once

#include "ISolutionQueryBuilder.h"
#include "IDataBaseCommand.h"
#include "IDataBaseCommandFactory.h"

namespace parcast
{

	class SqliteSolutionQueryBuilder : public ISolutionQueryBuilder
	{
	public:
		SqliteSolutionQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		virtual std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetUpdateQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteAllQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByUidQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetPatientUidCountQuery() const override;

	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}


