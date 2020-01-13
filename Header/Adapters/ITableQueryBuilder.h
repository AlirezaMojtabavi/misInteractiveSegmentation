#pragma once

#include "IDataBaseCommand.h"

namespace parcast
{

	class ITableQueryBuilder
	{
	public:
		virtual std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const = 0;

		virtual ~ITableQueryBuilder() = default;
	};

}
