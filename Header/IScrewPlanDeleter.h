#pragma once
#include "ISimpleDataPackage.h"
namespace parcast
{
	class IScrewPlanDeleter
	{
	public:
		virtual ~IScrewPlanDeleter() = default;
		virtual bool DeleteCurrentPlan(bool& modifyingPlanMode,
			std::shared_ptr<ISimpleDataPackage>,
			std::shared_ptr<parcast::IPlan> planUnderEdit,
			std::weak_ptr<parcast::IPlan> currentlySelectedPlan
		) = 0;


	};
	
}
