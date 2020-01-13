#pragma once
#include "IDataBaseCommandFactory.h"
#include "ISegemntedImageQueryBuilder.h"

namespace parcast
{

	class ISegemntedImageQueryBuilder 
	{
	public:
		virtual std::shared_ptr<IDataBaseCommand> GetCreateTableIfNotExistsQuery() const = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetInsertQuery() = 0;
		virtual std::shared_ptr<IDataBaseCommand> GetSelectBySolutionUidQuery() = 0;

	};

}