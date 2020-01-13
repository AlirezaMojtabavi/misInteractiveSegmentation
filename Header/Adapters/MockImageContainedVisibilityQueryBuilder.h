#pragma once

#include "IImageContainedVisibilityQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockImageContainedVisibilityQueryBuilder, IImageContainedVisibilityQueryBuilder)
	{
		MOCK_NON_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_NON_CONST_METHOD(GetSelectByImageContainedUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());

	};

}