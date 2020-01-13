#pragma once

#include "ICoordinateSystemQueryBuilder.h"
#include "IDataBaseCommandFactory.h"

namespace parcast
{

	class SqliteCoordinateSystemQueryBuilder : public ICoordinateSystemQueryBuilder
	{
	public:
		SqliteCoordinateSystemQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		virtual std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteQuery() const override;

	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}