#pragma once

#include "IDataBaseCommand.h"
#include "ITableQueryBuilder.h"

namespace parcast
{

	class IVolumeColormapQueryBuilder : public ITableQueryBuilder
	{
	public:

		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByVolumeUidQuery() = 0;
	};

}

