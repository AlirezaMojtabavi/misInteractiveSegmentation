#pragma once
#include "misPlanData.h"
#include "ISimpleDataPackage.h"

class IUpdatePlaning
{
public:
	virtual ~IUpdatePlaning() = default;
	virtual std::shared_ptr<misPlanData>   Update(	std::shared_ptr<ISimpleDataPackage> currentPackage) =  0;
};	