#pragma once
#include "ITableQueryBuilder.h"

#include "IDataBaseCommand.h"

namespace parcast
{
	class IImageQueryBuilder : public ITableQueryBuilder
	{
	public:
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetUpdateQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectBySolutionUidQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectUidsBySolutionUidQuery() const = 0;

		virtual ~IImageQueryBuilder() { }
	};
};
