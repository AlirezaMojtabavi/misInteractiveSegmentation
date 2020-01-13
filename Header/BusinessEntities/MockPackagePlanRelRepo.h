#pragma once

#include "IPackagePlanRelRepo.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPackagePlanRelRepo, IPackagePlanRelRepo)
	{
		MOCK_CONST_METHOD(GetByPlanUid, 1, std::vector<std::shared_ptr<IPackagePlanRel>>(const std::string& planUid));
		MOCK_CONST_METHOD(GetByPackageUid, 1, std::vector<std::shared_ptr<IPackagePlanRel>>(const std::string& packageUid));
		MOCK_NON_CONST_METHOD(Create, 2,
			std::shared_ptr<IPackagePlanRel>(std::shared_ptr<ISimpleDataPackage> package, std::shared_ptr<IPlan> plan));
		MOCK_NON_CONST_METHOD(DeleteByPackageUid, 1, void(const std::string& uid));
		MOCK_NON_CONST_METHOD(DeleteByPlanUid, 1, void(const std::string& uid));
		MOCK_NON_CONST_METHOD(Delete, 2, void(const std::string& pkgUid, const std::string& planUid));
		MOCK_CONST_METHOD(Get, 2, std::shared_ptr<IPackagePlanRel>(const std::string& pkgUid, const std::string& planUid));
	};

}