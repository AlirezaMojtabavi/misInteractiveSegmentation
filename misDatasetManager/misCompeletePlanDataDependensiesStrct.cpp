#include "stdafx.h"
#include "misCompeletePlanDataDependensiesStrct.h"
#include "IPlanRepo.h"
#include "IPackageRepo.h"

misCompeletePlanDataDependensiesStrct::misCompeletePlanDataDependensiesStrct(
	std::weak_ptr<parcast::IPackageRepo> packageRepo,
	std::weak_ptr<parcast::IPlanRepo> planRepo,
	const std::string& packageUid,
	const std::string& planUid)
	:m_PackageRepo(packageRepo),
	m_PlanRepo(planRepo),
	PackageUid(packageUid),
	PlanUid(planUid)
{
	transform = vtkSmartPointer<vtkTransform>::New();
	transform->Identity();
}


std::shared_ptr<parcast::IPlan> misCompeletePlanDataDependensiesStrct::GetPlanEntity()
{
	auto planRepo = m_PlanRepo.lock();
	
	if (!planRepo)
		return{};

	auto plan = planRepo->Get(PlanUid).lock();
	
	if (!plan)
		return{};
	
	return plan;
}

std::shared_ptr<ISimpleDataPackage> misCompeletePlanDataDependensiesStrct::GetPackage()
{
	auto packageRepo = m_PackageRepo.lock();
	
	if(packageRepo)
		return packageRepo->Get(PackageUid);

	return{};
}

void misCompeletePlanDataDependensiesStrct::SetVisibility(mis3DModelObjectOpacityPropertiesStrct visibility)
{
	m_Visibility = visibility;
}

mis3DModelObjectOpacityPropertiesStrct misCompeletePlanDataDependensiesStrct::GetVisibility()
{
	return m_Visibility;
}

