#pragma once
#include "IDataBaseCommand.h"
#include "ITableQueryBuilder.h"
namespace parcast
{
	class ISegmentedImageQueryBuilder : public ITableQueryBuilder
	{
	public:
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectByImageUidQuery() = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectUidsBySolutionUidQuery() const = 0;
	};
}