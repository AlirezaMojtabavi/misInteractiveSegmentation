#pragma once
#include "IPanoramicQueryBuilder.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockPanoramicQueryBuilder, IPanoramicQueryBuilder)
	{
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetRowCountQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetUpdateQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetSelectByImageUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
	};

}
