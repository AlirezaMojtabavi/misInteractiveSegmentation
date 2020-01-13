#pragma once

#include "ITmsNavAppCoreDependencyInjector.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockTmsNavAppCoreDependecyInjector, ITmsNavAppCoreDependencyInjector)
	{
		MOCK_CONST_METHOD(CreateApplicationContext, 0, std::shared_ptr<IApplicationContext>());
		MOCK_CONST_METHOD(CreateRootEntity, 0, std::shared_ptr<IRootEntity>());
		MOCK_CONST_METHOD(CreateSelectSolution, 0, std::shared_ptr<ISelectSolution>());
	};

}