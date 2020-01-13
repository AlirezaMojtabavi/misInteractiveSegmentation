#pragma once

#include "IImageContainedPropertiesQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockImageContainedPropertiesQueryBuilder, IImageContainedPropertiesQueryBuilder)
	{
		MOCK_NON_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_NON_CONST_METHOD(GetSelectByImageContainedPolyDataUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());
	};

}
