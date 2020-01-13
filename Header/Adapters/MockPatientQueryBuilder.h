#pragma once

#include "IPatientQueryBuilder.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPatientQueryBuilder, IPatientQueryBuilder)
	{
		MOCK_CONST_METHOD(GetCreateTableIfNotExistsQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetInsertQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetDeleteQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetRowCountQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetUpdateQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetSelectByUidQuery, 0, std::shared_ptr<IDataBaseCommand>());
		MOCK_CONST_METHOD(GetDeleteAllQuery, 0, std::shared_ptr<IDataBaseCommand>());
	};

}
