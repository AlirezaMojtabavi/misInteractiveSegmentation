#pragma once

#include "IRootEntity.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockRootEntity, IRootEntity)
	{
		MOCK_CONST_METHOD(GetCurrentSolution, 0, std::shared_ptr<ITreatmentSolution>());
	};

}