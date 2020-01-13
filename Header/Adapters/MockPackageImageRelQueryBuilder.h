#pragma once

#include "IPackageImageRelQueryBuilder.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockPackageImageRelQueryBuilder, IPackageImageRelQueryBuilder)
	{
		MOCK_CONST_METHOD(GetRowCountQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetUpdateQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetSelectByPackageUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetDeleteByImageUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
	};
}
