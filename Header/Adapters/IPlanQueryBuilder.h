#pragma once

#include "IDataBaseCommand.h"
#include "ITableQueryBuilder.h"

namespace parcast
{

	class IPlanQueryBuilder : public ITableQueryBuilder
	{
	public:

		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectBySolutionUidQuery() = 0;
	};

}
