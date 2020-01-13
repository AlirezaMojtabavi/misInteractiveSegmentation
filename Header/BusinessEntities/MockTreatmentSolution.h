#pragma once

#include "ITreatmentSolution.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockTreatmentSolution, ITreatmentSolution)
	{
		MOCK_CONST_METHOD(GetPackages, 0, std::vector<std::shared_ptr<ISimpleDataPackage>>());
	};

} 