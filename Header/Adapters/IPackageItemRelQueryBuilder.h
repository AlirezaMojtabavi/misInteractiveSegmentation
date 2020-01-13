#pragma once
#include "ITableQueryBuilder.h"

#include "IDataBaseCommand.h"

namespace parcast
{

	class IPackageItemRelQueryBuilder : public ITableQueryBuilder
	{
	public:
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByPackageUidQuery() = 0;
	};

}