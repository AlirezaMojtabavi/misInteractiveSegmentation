#pragma once

#include "IDataBaseCommandFactory.h"
#include "IPackageImageRelQueryBuilder.h"

namespace parcast
{

	class SqlitePackageImageRelQueryBuilder : public IPackageImageRelQueryBuilder
	{
	public:
		SqlitePackageImageRelQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetUpdateQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByPackageUidQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteByImageUidQuery() const override;

	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}
