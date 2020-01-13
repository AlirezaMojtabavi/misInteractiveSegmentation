#pragma once

#include "ITreatmentSolution.h"

namespace parcast
{

	// 
	class ITreatmentSolutionRepo
	{
	public:
		typedef long long int IdType;

		virtual std::shared_ptr<ITreatmentSolution> AddNew(
			const std::string& firstName, const std::string& lastName, Sex sex, const DateTime& birthDate) const = 0;
		virtual void Remove(IdType solutionId) = 0;
		virtual void Modify(IdType solutionId) = 0;
		virtual std::vector<std::shared_ptr<ITreatmentSolution>> GetAll() const = 0;

		virtual ~ITreatmentSolutionRepo() {}
	};

}
