#pragma once

#include "IPackageItemQueryBuilder.h"

namespace parcast
{
	class IDataBaseCommandFactory;

	class SqlitePackageItemQueryBuilder : public IPackageItemQueryBuilder
	{
	public:
		SqlitePackageItemQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> dbCommandFactory);

		std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetInsertQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;

	private:
		std::shared_ptr<IDataBaseCommandFactory> m_DbCommandFactory;
	};

}
