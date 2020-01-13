#pragma once
#include "IPackagePlanRelFactory.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPackagePlanRelFactory, IPackagePlanRelFactory)
	{
		MOCK_CONST_METHOD(Create, 2, std::shared_ptr<IPackagePlanRel>(const std::string& packegUid, const std::string& planUid));
	};

}
