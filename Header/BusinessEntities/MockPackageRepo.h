#pragma once

#include "IPackageRepo.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPackageRepo, IPackageRepo)
	{
		MOCK_CONST_METHOD(Get, 1, std::shared_ptr<ISimpleDataPackage>(const std::string& packageUid));
		MOCK_CONST_METHOD(GetBySolutionId, 1, 
			std::vector<std::shared_ptr<ISimpleDataPackage>>(const std::string& solutionId));
	};

}
