#pragma once

#include "ITableQueryBuilder.h"

namespace parcast
{

	class IPackageVolumeQueryBuilder : public ITableQueryBuilder
	{
	public:
		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByPackageUidQuery() const = 0;
	};

}
