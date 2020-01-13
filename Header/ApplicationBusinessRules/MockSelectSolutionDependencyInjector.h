#pragma once

#include "ISelectSolutionDependencyInjector.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockSelectSolutionDependencyInjector, ISelectSolutionDependencyInjector)
	{
		MOCK_CONST_METHOD(CreateTreatmentSolution, 6, std::shared_ptr<ITreatmentSolution>(
			const std::string& firstName, const std::string& lastName, Sex sex,
			const DateTime& birthDate, const DateTime& createdDate, const DateTime& lastModifiedDate));
		MOCK_CONST_METHOD(CreateClock, 0, std::shared_ptr<IClock>());
		
	};

}

