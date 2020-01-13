#pragma once

#include "ISelectSolution.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockSelectSolution, ISelectSolution)
	{
		MOCK_NON_CONST_METHOD(CreateNewSolution, 4, 
			void(const std::string& firstName, const std::string& lastName, Sex sex, const DateTime& birthDate));
	};

}

