#pragma once

#include "ICoordinateSystemQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockCoordinateSystemQueryBuilder, ICoordinateSystemQueryBuilder)
	{
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetRowCountQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetDeleteQuery, 0, std::shared_ptr<IDataBaseCommand>());
	};

}