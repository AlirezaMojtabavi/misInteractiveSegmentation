#pragma once
#include "ITableQueryBuilder.h"
#include "IDataBaseCommand.h"

namespace parcast
{
	class IPanoramicQueryBuilder : public ITableQueryBuilder
	{
	public:
		virtual ~IPanoramicQueryBuilder() = default;

		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetUpdateQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByImageUidQuery() const = 0;
	};
}

