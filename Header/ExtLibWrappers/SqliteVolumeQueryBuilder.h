#pragma once


#include "IDataBaseCommandFactory.h"
#include "IVolumeQueryBuilder.h"

namespace parcast
{

	class SqliteVolumeQueryBuilder : public IVolumeQueryBuilder
	{
	public:
		SqliteVolumeQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetInsertQuery() override;
		std::shared_ptr<IDataBaseCommand> GetSelectBySolutionUidQuery() override;

	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}