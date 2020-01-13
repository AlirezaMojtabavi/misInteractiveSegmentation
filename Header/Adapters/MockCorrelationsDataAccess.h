#pragma once
#include "ICorrelationDataAccess.h"
namespace parcast
{
	MOCK_BASE_CLASS(MockCorrelationsDataAccess, ICorrelationDataAccess)
	{
		MOCK_NON_CONST_METHOD(Insert, 1, void(const std::vector<CorrelationData>& list));
		MOCK_NON_CONST_METHOD(GetBySolutionUid, 1, std::vector<CorrelationData>(const std::string& uid));
		MOCK_NON_CONST_METHOD(DeleteBySolutionUid, 1, void(const std::string& uid));
		MOCK_NON_CONST_METHOD(DeleteByCoordSysUid, 1, void(const std::string& uid));
		MOCK_NON_CONST_METHOD(DeleteAll, 0, void());
	};
}
