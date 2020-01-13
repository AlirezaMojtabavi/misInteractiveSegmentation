#pragma once

#include "IPackageItemRelQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPackageItemRelQueryBuilder, IPackageItemRelQueryBuilder)
	{
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_NON_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_NON_CONST_METHOD(GetSelectByPackageUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
	};
	
}

