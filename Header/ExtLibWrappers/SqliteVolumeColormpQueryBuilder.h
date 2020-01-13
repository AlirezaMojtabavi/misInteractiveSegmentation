#pragma once
#include "IDataBaseCommandFactory.h"
#include "IVolumeColormapQueryBuilder.h"

namespace parcast
{

	class SqliteVolumeColormpQueryBuilder : public IVolumeColormapQueryBuilder
	{
	public:
		SqliteVolumeColormpQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetInsertQuery() override;
 
		std::shared_ptr<parcast::IDataBaseCommand> GetSelectByVolumeUidQuery() override;
	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}