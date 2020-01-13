#pragma once
#include "misVertebraScrewPlanData.h"
#include "ISimpleDataPackage.h"

class IScrewCreator
{
public:

	virtual std::weak_ptr<parcast::IPlan> CreateScrew(std::shared_ptr<ISimpleDataPackage> package, const misColorStruct& color, double screwDiameter) = 0;
	virtual  ~IScrewCreator() = default;
};

