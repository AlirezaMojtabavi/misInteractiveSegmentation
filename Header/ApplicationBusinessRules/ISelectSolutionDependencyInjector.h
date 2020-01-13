#pragma once

#include "ITreatmentSolution.h"
#include "IClock.h"

namespace parcast
{

	class ISelectSolutionDependencyInjector
	{
	public:
		virtual std::shared_ptr<ITreatmentSolution> CreateTreatmentSolution(
			const std::string& firstName, const std::string& lastName, Sex sex, 
			const DateTime& birthDate, const DateTime& createdDate, const DateTime& lastModifiedDate) const = 0;
		virtual std::shared_ptr<IClock> CreateClock() const = 0;

		virtual ~ISelectSolutionDependencyInjector() { }
	};

}
