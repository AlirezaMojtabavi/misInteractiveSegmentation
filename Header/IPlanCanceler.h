#pragma once
#include "ISimpleDataPackage.h"

class  IPlanCanceler
{
public:
	virtual void CancelPlan(std::shared_ptr<ISimpleDataPackage> package,
	                        std::weak_ptr<parcast::IPlan> currentPlan) = 0;
	virtual ~IPlanCanceler() = default;
};
