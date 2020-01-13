#pragma once
#include "IPackagePlanRelFactory.h"

namespace parcast
{

	class PackagePlanRelFactory : public IPackagePlanRelFactory
	{
	public:
		PackagePlanRelFactory(std::weak_ptr<IPackageRepo> packageRepo, std::weak_ptr<IPlanRepo> planRepo);
		std::shared_ptr<IPackagePlanRel> Create(const std::string& packegUid, const std::string& planUid) const override;

	private:
		std::weak_ptr<IPackageRepo> m_PackageRepo;
		std::weak_ptr<IPlanRepo> m_PlanRepo;

	};

}
