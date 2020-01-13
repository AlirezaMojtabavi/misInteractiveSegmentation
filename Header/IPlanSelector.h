#pragma once
#include "ISimpleDataPackage.h"

class IPlanSelector
{
public:
	virtual void SelectPlan(std::shared_ptr<ISimpleDataPackage> package, std::weak_ptr<parcast::IPlan> plan) = 0;
	virtual  ~IPlanSelector() = default;
};
