#pragma once
#include "IImageQueryBuilder.h"
#include "DataBaseCommand.h"
#include "IDataBaseCommandFactory.h"

namespace parcast
{

	class SqliteImageQueryBuilder : public IImageQueryBuilder
	{
	public:
		SqliteImageQueryBuilder(std::shared_ptr<IDataBaseCommandFactory> commandFactory);

		virtual std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetUpdateQuery() const override;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectBySolutionUidQuery() const;;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectUidsBySolutionUidQuery() const;;

	private:
		std::shared_ptr<IDataBaseCommandFactory> m_CommandFactory;
	};

}
