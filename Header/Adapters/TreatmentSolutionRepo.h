#pragma once

#include "ITreatmentSolutionRepo.h"
#include "IClock.h"

namespace parcast
{

	class TreatmentSolutionRepo : public ITreatmentSolutionRepo
	{
	public:
		TreatmentSolutionRepo();

		virtual std::shared_ptr<ITreatmentSolution> AddNew(
			const std::string& firstName, const std::string& lastName, Sex sex, const DateTime& birthDate) const override;
		virtual void Remove(IdType solutionId) override;
		virtual void Modify(IdType solutionId) override;
		virtual std::vector<std::shared_ptr<ITreatmentSolution>> GetAll() const override;
	private:
		
	};

}
