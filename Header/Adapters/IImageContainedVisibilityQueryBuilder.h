#pragma once

#include "ITableQueryBuilder.h"

#include "IDataBaseCommand.h"

namespace parcast
{

	class IImageContainedVisibilityQueryBuilder : public ITableQueryBuilder
	{
	public:
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByImageContainedUidQuery() = 0;
	};

}