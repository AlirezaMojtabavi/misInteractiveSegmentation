#pragma once

#include "IDataBaseConnection.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockDataBaseConnection, IDataBaseConnection)
	{
		MOCK_NON_CONST_METHOD(Open, 0, void());
		MOCK_CONST_METHOD(IsOpen, 0, bool());
		MOCK_NON_CONST_METHOD(SetFilePath, 1, void(const std::string& path));
		MOCK_NON_CONST_METHOD(Close, 0, void());
		MOCK_NON_CONST_METHOD(Exec, 1, std::shared_ptr<IQueryResult> (std::shared_ptr<const IDataBaseCommand> dbCommand));
	};
	
}
