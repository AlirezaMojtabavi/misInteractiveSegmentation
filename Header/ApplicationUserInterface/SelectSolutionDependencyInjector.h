#pragma once

#include "ISelectSolutionDependencyInjector.h"

namespace parcast
{

	class SelectSolutionDependencyInjector : public ISelectSolutionDependencyInjector
	{
	public:
		virtual std::shared_ptr<ITreatmentSolution> CreateTreatmentSolution(
			const std::string& firstName, const std::string& lastName, Sex sex, 
			const DateTime& birthDate, const DateTime& createdDate, const DateTime& lastModifiedDate) const override;
		virtual std::shared_ptr<IClock> CreateClock() const override;
	};

}
