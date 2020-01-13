#pragma once
#include "IVolumeVisibiltyQueryBuilder.h"

#include "IDataBaseCommandFactory.h"

namespace parcast
{

	class SqliteVolumeVisibiltyQueryBuilder : public IVolumeVisibiltyQueryBuilder
	{
	public:
		SqliteVolumeVisibiltyQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetInsertQuery() override;
		std::shared_ptr<IDataBaseCommand> GetSelectByVolumeUidQuery() override;

	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}