#pragma once
#include "ITableQueryBuilder.h"

#include "IDataBaseCommand.h"

namespace parcast
{

	class ICoordinateSystemQueryBuilder : public ITableQueryBuilder
	{
	public:
		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteQuery() const = 0;

		virtual ~ICoordinateSystemQueryBuilder() = default;
	};

}
