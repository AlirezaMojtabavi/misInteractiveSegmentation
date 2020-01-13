#pragma once

#include "ITableQueryBuilder.h"

namespace parcast
{

	class ILandmarkQueryBuilder : public ITableQueryBuilder
	{
	public:
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByPackageUidQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteByPackageUidQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const = 0;

			virtual ~ILandmarkQueryBuilder() { }

	};

}