#pragma once

#include "IApplicationContext.h"
#include "IRootEntity.h"
#include "ISelectSolution.h"

namespace parcast
{

	class ITmsNavAppCoreDependencyInjector
	{
	public:
		virtual std::shared_ptr<IApplicationContext> CreateApplicationContext() const = 0;
		virtual std::shared_ptr<IRootEntity> CreateRootEntity() const = 0;
		virtual std::shared_ptr<ISelectSolution> CreateSelectSolution() const = 0;
		
		virtual ~ITmsNavAppCoreDependencyInjector() { }
	};

}
