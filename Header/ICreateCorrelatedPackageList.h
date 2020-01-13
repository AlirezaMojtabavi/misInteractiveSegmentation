#pragma once
class ICreateCorrelatedPackageList
{
public:

	virtual void CreateCorrelatedPackageList() = 0; 
	virtual ~ICreateCorrelatedPackageList() = default;
};
