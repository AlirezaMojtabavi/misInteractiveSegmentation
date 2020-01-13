#pragma once

#include "IPackageVolumeQueryBuilder.h"

namespace parcast
{
	class IDataBaseCommandFactory;

	class SqlitePackageVolumeQueryBuilder : public IPackageVolumeQueryBuilder
	{
	public:
		SqlitePackageVolumeQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> dbCommandFactory);

		std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetInsertQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;

		virtual std::shared_ptr<IDataBaseCommand> GetSelectByPackageUidQuery() const override;

	private:
		std::shared_ptr<IDataBaseCommandFactory> m_DbCommandFactory;
	};

}
