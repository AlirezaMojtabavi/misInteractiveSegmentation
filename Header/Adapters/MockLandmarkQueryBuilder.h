#pragma once

#include "ILandmarkQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockLandmarkQueryBuilder, ILandmarkQueryBuilder)
	{
		MOCK_CONST_METHOD(GetDeleteByPackageUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetSelectByPackageUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());
	};

}
