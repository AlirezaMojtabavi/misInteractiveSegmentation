#include "stdafx.h"
#include "PackagePlanRelFactory.h"

parcast::PackagePlanRelFactory::PackagePlanRelFactory(std::weak_ptr<IPackageRepo> packageRepo, std::weak_ptr<IPlanRepo> planRepo)
	: m_PackageRepo(packageRepo), m_PlanRepo(planRepo)
{
}

std::shared_ptr<parcast::IPackagePlanRel> parcast::PackagePlanRelFactory::Create(
	const std::string& packegUid, const std::string& planUid) const
{
	return std::make_shared<misCompeletePlanDataDependensiesStrct>(m_PackageRepo, m_PlanRepo, packegUid, planUid);
}