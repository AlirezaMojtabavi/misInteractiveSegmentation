#pragma once
#include "ISimpleDataPackage.h"
class IScrewDisplayer
{
public:
	virtual ~IScrewDisplayer() = default;
	virtual void ShowScrews(std::shared_ptr<ISimpleDataPackage> package) = 0;
	
};
