#pragma once
#include "ITreatmentSolution.h"
#include "ISolutionChangedObserver.h"
#include <memory>

namespace parcast
{

	// The IApplicationContext class provides the abstract interface to access current application context such as currently 
	// selection treatment solution object, etc. Observers could be added to the application context to receive notifications on
	// various events such as CurrentSolutionChanged, etc.
	class IApplicationContext
	{
	public:
		virtual void SetCurrentTreatmentSolution(std::shared_ptr<ITreatmentSolution> treatmentSolution) = 0;
		virtual std::shared_ptr<ITreatmentSolution> GetCurrentTreatmentSolution() const = 0;
		virtual void AddSolutionChangedObserver(std::weak_ptr<ISolutionChangedObserver> observer) = 0;
		virtual ~IApplicationContext() { }
	};

}


