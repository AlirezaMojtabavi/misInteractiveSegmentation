#pragma once

#include "IApplicationContext.h"
#include "IRootEntity.h"
#include "ISelectSolution.h"
#include "ISelectSolutionDependencyInjector.h"

namespace parcast
{

	// The SelectSolution class provides the logic for the first step of the TMSNav application. It enables the user interface 
	// to create a treatment solution or select a previously created solution.
	class SelectSolution : public ISelectSolution
	{
	public:
		SelectSolution(std::shared_ptr<ISelectSolutionDependencyInjector> injector, 
			std::shared_ptr<IApplicationContext> appContext, std::shared_ptr<IRootEntity> rootEntity);

		void CreateNewSolution(const std::string& firstName, const std::string& lastName, Sex sex, const DateTime& birthDate);

	private:
		std::shared_ptr<ISelectSolutionDependencyInjector> m_Injector;
		std::shared_ptr<IApplicationContext> m_AppContext;
		std::shared_ptr<IRootEntity> m_RootEntity;
	};

}