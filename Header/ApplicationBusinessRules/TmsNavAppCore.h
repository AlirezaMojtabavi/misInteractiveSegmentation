#pragma once

#include "ISelectSolution.h"
#include "ITmsNavAppCoreDependencyInjector.h"

namespace parcast
{

	class TmsNavAppCore
	{
	public:
		TmsNavAppCore(std::shared_ptr<ITmsNavAppCoreDependencyInjector> injector);
		~TmsNavAppCore();

		std::shared_ptr<ISelectSolution> GetSelectSolution();
		
		void UpdateStatus();

	private:
		void CreateSubsystems();

		std::shared_ptr<ITmsNavAppCoreDependencyInjector> m_Injector;
		std::shared_ptr<IApplicationContext> m_ApplicationContext;
		std::shared_ptr<ISelectSolution> m_SelectSolution;
		
	};

}