#pragma once

#include "IRootEntity.h"
#include "ITreatmentSolutionRepo.h"

namespace parcast
{

	class RootEntity : public IRootEntity
	{
	public:
		RootEntity(std::shared_ptr<ITreatmentSolutionRepo> repository);
		virtual std::vector< std::shared_ptr<ITreatmentSolution> > GetAllSolutions() const override; 
		virtual std::shared_ptr<ITreatmentSolution> AddNewSolution(
			const std::string& firstName, const std::string& lastName, Sex sex, const DateTime& birthDate) override;

	private:
		std::shared_ptr<ITreatmentSolutionRepo> m_Repository;
	};

}