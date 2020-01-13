#pragma once
#include "ILandmarkDataAccess.h"

namespace  parcast
{
	MOCK_BASE_CLASS(MockLandmarkDataAccess, ILandmarkDataAccess)
	{
		MOCK_NON_CONST_METHOD(DeleteByPackageUid, 1, void(const std::string& uid));
		MOCK_NON_CONST_METHOD(Insert, 1, void(const LandmarkData& data));
		MOCK_NON_CONST_METHOD(GetByPackageUid, 1, std::vector<LandmarkData>(const std::string& uid));
	};
}
