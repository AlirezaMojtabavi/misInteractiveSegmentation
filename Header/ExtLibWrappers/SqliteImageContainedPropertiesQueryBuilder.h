#pragma once
#include "IDataBaseCommandFactory.h"
#include "IImageContainedPropertiesQueryBuilder.h"

namespace parcast
{

	class SqliteImageContainedPropertiesQueryBuilder : public IImageContainedPropertiesQueryBuilder
	{
	public:
		SqliteImageContainedPropertiesQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetInsertQuery() override;
		std::shared_ptr<parcast::IDataBaseCommand> GetSelectByImageContainedPolyDataUidQuery() override;
	
	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}