#pragma once
#include "ITreatmentSolution.h"

namespace parcast
{

	class ISolutionChangedObserver
	{
	public:
		virtual void CurrentSolutionChanged(std::shared_ptr<ITreatmentSolution> lastSolution) = 0;

		virtual ~ISolutionChangedObserver() { }
	};

}