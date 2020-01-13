#pragma once

#include "ITreatmentSolution.h"
#include "ITreatmentSolutionRepo.h"
#include <memory>

namespace parcast
{
	// The ITreatmentSolutionFactory class provides the abstract interface to a Factory that creates TreatmentSolutions

	class ITreatmentSolutionFactory
	{
	public:
		typedef long long int IdType;
		virtual std::shared_ptr<ITreatmentSolution> CreateTreatmentSolution() const = 0;

		virtual ~ITreatmentSolutionFactory() {}
	};

}