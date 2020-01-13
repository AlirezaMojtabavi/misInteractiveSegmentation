#pragma once

#include "IVolumeQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockVolumeQueryBuilder, IVolumeQueryBuilder)
	{
		MOCK_NON_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_NON_CONST_METHOD(GetSelectBySolutionUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());
	};

}