#pragma once
#include "IPackageItemRelQueryBuilder.h"

#include "IDataBaseCommandFactory.h"

namespace parcast
{

	class SqlitePackageItemRelQueryBuilder : public IPackageItemRelQueryBuilder
	{
	public:
		SqlitePackageItemRelQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetInsertQuery() override;
		std::shared_ptr<IDataBaseCommand> GetSelectByPackageUidQuery() override;

	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}