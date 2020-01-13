#pragma once
#include "IDataBaseCommandFactory.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockDataBaseCommandFactory, IDataBaseCommandFactory)
	{
		MOCK_NON_CONST_METHOD(CreateCommand, 0, std::shared_ptr<IDataBaseCommand>());
	};

}

