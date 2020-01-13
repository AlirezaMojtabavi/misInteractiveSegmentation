#pragma once
#include "ISolutionChangedObserver.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockSolutionChangedObserver, ISolutionChangedObserver)
	{
		MOCK_NON_CONST_METHOD(CurrentSolutionChanged, 1, void (std::shared_ptr<ITreatmentSolution> lastSolution));
	};

}