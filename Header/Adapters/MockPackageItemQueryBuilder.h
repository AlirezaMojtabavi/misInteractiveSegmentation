#pragma once

#include "IPackageItemQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPackageItemQueryBuilder, IPackageItemQueryBuilder)
	{
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetRowCountQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
	};

}