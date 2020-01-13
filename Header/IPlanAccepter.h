#pragma once
#include "misPlanSTRCT.h"
class IPlanAccepter
{
public:
	virtual ~IPlanAccepter() = default;
	virtual void AcceptPlan(std::weak_ptr<parcast::IPlan> , const ScrewPlanInformation& planInfo) = 0;
};

 