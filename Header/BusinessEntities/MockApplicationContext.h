#pragma once
#include "IApplicationContext.h"
#include "ITreatmentSolution.h"
#include "ISolutionChangedObserver.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockApplicationContext, IApplicationContext)
	{
		MOCK_NON_CONST_METHOD(SetCurrentTreatmentSolution, 1, void(std::shared_ptr<ITreatmentSolution>));
		MOCK_CONST_METHOD(GetCurrentTreatmentSolution, 0, std::shared_ptr<ITreatmentSolution>());
		MOCK_NON_CONST_METHOD(AddSolutionChangedObserver, 1, void(std::weak_ptr<ISolutionChangedObserver>));
	};
}