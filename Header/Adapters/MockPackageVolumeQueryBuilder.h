#pragma once

#include "IPackageVolumeQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPackageVolumeQueryBuilder, IPackageVolumeQueryBuilder)
	{
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetRowCountQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetSelectByPackageUidQuery, 0, std::shared_ptr<IDataBaseCommand>());

	};

}