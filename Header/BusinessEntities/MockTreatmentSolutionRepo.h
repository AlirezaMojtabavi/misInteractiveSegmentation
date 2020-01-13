#pragma once

#include "ITreatmentSolutionRepo.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockTreatmentSolutionRepo, ITreatmentSolutionRepo)
	{
		MOCK_CONST_METHOD(AddNew, 4, std::shared_ptr<ITreatmentSolution> (
			const std::string& firstName, const std::string& lastName, Sex sex, const DateTime& birthDate));
		MOCK_NON_CONST_METHOD(Remove, 1, void (IdType));
		MOCK_NON_CONST_METHOD(Modify, 1, void (IdType));
		MOCK_CONST_METHOD(GetAll, 0, std::vector<std::shared_ptr<ITreatmentSolution>>());
	};

}
