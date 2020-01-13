#pragma once

#include "IVolumeColormapQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockVolumeColormapQueryBuilder, IVolumeColormapQueryBuilder)
	{
		MOCK_NON_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_NON_CONST_METHOD(GetSelectByVolumeUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0 , std::shared_ptr<IDataBaseCommand> () );
 	};

}