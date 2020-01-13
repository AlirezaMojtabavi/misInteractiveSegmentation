#pragma once
#include "IApplicationContext.h"

namespace parcast
{


	class ApplicationContext : public parcast::IApplicationContext
	{
	public:
		ApplicationContext();

		virtual void SetCurrentTreatmentSolution(std::shared_ptr<ITreatmentSolution> treatmentSolution) override;
		virtual std::shared_ptr<ITreatmentSolution> GetCurrentTreatmentSolution() const override;
		virtual void AddSolutionChangedObserver(std::weak_ptr<ISolutionChangedObserver> observer) override;

	private:
		std::shared_ptr<ITreatmentSolution> m_CurrentTreatmentSolution;
		std::vector< std::weak_ptr<ISolutionChangedObserver> > m_SolutionChangedObservers;
	};

}