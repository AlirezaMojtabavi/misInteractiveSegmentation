#pragma once
class IPackageViewerAbstract
{
public:
	virtual void ShowPlan(std::shared_ptr<misCompeletePlanDataDependensiesStrct> rel) = 0;

	~IPackageViewerAbstract(){}
};
