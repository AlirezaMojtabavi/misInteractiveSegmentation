#pragma once
#include "ITableQueryBuilder.h"

#include "IDataBaseCommand.h"

namespace parcast
{

	class ICorrelationQueryBuilder : public ITableQueryBuilder
	{

	public:
		virtual ~ICorrelationQueryBuilder() = default;

		virtual std::shared_ptr<IDataBaseCommand> GetRowCountQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectBySolutionUidQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteBySolutionUidQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteBySourceUidQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteByDestinationUidQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetDeleteAllQuery() const = 0;
	};

}
