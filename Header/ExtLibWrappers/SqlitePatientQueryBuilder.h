#pragma once

#include "IDataBaseCommandFactory.h"
#include "IPatientQueryBuilder.h"

namespace parcast
{

	class SqlitePatientQueryBuilder : public IPatientQueryBuilder
	{
	public:
		SqlitePatientQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		virtual std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetUpdateQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByUidQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteAllQuery() const override;

	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}