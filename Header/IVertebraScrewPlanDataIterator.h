#pragma once
#include "misVertebraScrewPlanData.h"
#include "ISimpleDataPackage.h"

class IVertebraScrewPlanDataIterator
{
public:
	virtual ~IVertebraScrewPlanDataIterator() = default;
	using FunctionType = std::function<void(std::weak_ptr<misVertebraScrewPlanData>)>;
	virtual void DoForSelectedVertebraScrewPlan(FunctionType toDo, std::shared_ptr<ISimpleDataPackage> package) = 0;

};
