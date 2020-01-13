#pragma once

#include "ISegmentedImageQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockSegmentedImageQueryBuilder, ISegmentedImageQueryBuilder)
	{
		MOCK_NON_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_NON_CONST_METHOD(GetSelectByImageUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetSelectUidsBySolutionUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());

	};

}

 