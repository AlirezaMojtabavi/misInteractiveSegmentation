#pragma once

#include "IDatabaseInitializer.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockDatabaseInitializer, IDatabaseInitializer)
	{
		MOCK_NON_CONST_METHOD(AddQuerybuilder, 1, void(std::shared_ptr<ITableQueryBuilder> queryBuilder));
		MOCK_CONST_METHOD(Initialize, 0, void());
	};

}
