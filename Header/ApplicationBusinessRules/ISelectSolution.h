#pragma once

#include "DateTime.h"
#include "Sex.h"

namespace parcast
{

	class ISelectSolution
	{
	public:
		virtual void CreateNewSolution(
			const std::string& firstName, const std::string& lastName, Sex sex, const DateTime& birthDate) = 0;

		virtual ~ISelectSolution() { }
	};

}