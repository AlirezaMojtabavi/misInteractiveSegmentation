#pragma once

#include "ITmsNavAppCoreDependencyInjector.h"

namespace parcast
{

	class TmsNavAppCoreDependencyInjector : public ITmsNavAppCoreDependencyInjector
	{
	public:
		TmsNavAppCoreDependencyInjector();
		virtual std::shared_ptr<ISelectSolution> CreateSelectSolution() const override;
		virtual std::shared_ptr<IRootEntity> CreateRootEntity() const override;
		virtual std::shared_ptr<IApplicationContext> CreateApplicationContext() const override;
		
	private:
		std::shared_ptr<IApplicationContext> m_ApplicationContext;
		std::shared_ptr<IRootEntity> m_RootEntity;
	};

}