#pragma once
#include "IImageContainedVisibilityQueryBuilder.h"

#include "IDataBaseCommandFactory.h"

namespace parcast
{

	class SqliteImageContainedVisibilityQueryBuilder : public IImageContainedVisibilityQueryBuilder
	{
	public:
		SqliteImageContainedVisibilityQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		std::shared_ptr<IDataBaseCommand> GetInsertQuery() override;
		std::shared_ptr<IDataBaseCommand> GetSelectByImageContainedUidQuery() override;

	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}