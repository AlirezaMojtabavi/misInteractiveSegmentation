#pragma once

#include "IDataBaseCommandFactory.h"
#include "IPackageQueryBuilder.h"

namespace parcast
{

	class SqlitePackageQueryBuilder : public IPackageQueryBuilder
	{
	public:
		SqlitePackageQueryBuilder(std::shared_ptr<parcast::IDataBaseCommandFactory> commandFactory);

		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetUpdateQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectBySolutionUidQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;

	private:
		std::shared_ptr<parcast::IDataBaseCommandFactory> m_CommandFactory;
	};

}