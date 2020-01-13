#pragma once

#include "ITableQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockTableQueryBuilder, ITableQueryBuilder)
	{
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());
	};

}
