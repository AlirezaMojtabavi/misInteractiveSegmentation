#pragma once


#include "misPlanData.h"
#include "IPlan.h"
#include "IPackagePlanRel.h"
namespace parcast 
{
	class IPackageRepo;
	class IPlanRepo;
}
class mis3DModelObjectOpacityPropertiesStrct;
class misCompeletePlanDataDependensiesStrct : public parcast::IPackagePlanRel
{
public:
	misCompeletePlanDataDependensiesStrct(
		std::weak_ptr<parcast::IPackageRepo> packageRepo,
		std::weak_ptr<parcast::IPlanRepo> planRepo,
		const std::string& packageUid, 
		const std::string& planUid);


	std::shared_ptr<parcast::IPlan> GetPlanEntity() override;
	std::shared_ptr<ISimpleDataPackage> GetPackage() override;
	vtkSmartPointer<vtkTransform>   transform;
	void SetVisibility(mis3DModelObjectOpacityPropertiesStrct visibility) override;
	mis3DModelObjectOpacityPropertiesStrct  GetVisibility() override;
	void operator=(parcast::IPackagePlanRel& right ) override = delete;


private:
	const std::string PackageUid;
	const std::string PlanUid;

	mis3DModelObjectOpacityPropertiesStrct m_Visibility;
	std::weak_ptr<parcast::IPackageRepo> m_PackageRepo;
	std::weak_ptr<parcast::IPlanRepo> m_PlanRepo;
};
