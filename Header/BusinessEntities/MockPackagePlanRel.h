#pragma once
#include "IPackagePlanRel.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPackagePlanRel, IPackagePlanRel)
	{
		MOCK_NON_CONST_METHOD(GetPlanEntity, 0, std::shared_ptr<IPlan>());
		MOCK_NON_CONST_METHOD(GetPackage, 0, std::shared_ptr<ISimpleDataPackage>());
		MOCK_NON_CONST_METHOD(SetVisibility, 1, void(mis3DModelObjectOpacityPropertiesStrct visibility));
		MOCK_NON_CONST_METHOD(GetVisibility, 0, mis3DModelObjectOpacityPropertiesStrct());
		MOCK_NON_CONST_METHOD(operator=, 1, void(const parcast::MockPackagePlanRel&), assignment); // operators require a custom identifier
	};

}