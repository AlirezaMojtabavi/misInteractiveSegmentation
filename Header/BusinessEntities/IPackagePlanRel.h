#pragma once

#include "mis3DModelViewingProperties.h"

class ISimpleDataPackage;

namespace parcast
{

	class IPlan;

	class IPackagePlanRel
	{
	public :
		virtual ~IPackagePlanRel() = default;
		
		virtual std::shared_ptr<IPlan> GetPlanEntity() = 0;
		virtual std::shared_ptr<ISimpleDataPackage> GetPackage() = 0;
		virtual void SetVisibility(mis3DModelObjectOpacityPropertiesStrct visibility) = 0;
		virtual mis3DModelObjectOpacityPropertiesStrct  GetVisibility() = 0;
		virtual void IPackagePlanRel::operator=(parcast::IPackagePlanRel& right) = delete;
	};
	
}
typedef  std::vector<std::shared_ptr<parcast::IPackagePlanRel>> PlanDataListDependencyTypedef;