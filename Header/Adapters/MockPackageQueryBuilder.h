#pragma once

#include "IPackageQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPackageQueryBuilder, IPackageQueryBuilder)
	{
		MOCK_CONST_METHOD(GetRowCountQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetUpdateQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetSelectBySolutionUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());
	};

}