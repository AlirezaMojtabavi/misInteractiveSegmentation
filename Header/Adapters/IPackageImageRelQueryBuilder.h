#pragma once
#include "ITableQueryBuilder.h"

#include "IDataBaseCommand.h"

namespace parcast
{
	class IPackageImageRelQueryBuilder : public ITableQueryBuilder
	{
	public:
		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByPackageUidQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetUpdateQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteByImageUidQuery() const = 0;

		virtual ~IPackageImageRelQueryBuilder() { }
	};
}
