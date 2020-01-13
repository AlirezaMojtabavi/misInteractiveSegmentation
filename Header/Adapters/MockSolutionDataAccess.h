#pragma once

#include "SolutionData.h"
#include "ISolutionDataAccess.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockSolutionDataAccess, ISolutionDataAccess)
	{
		MOCK_NON_CONST_METHOD(GetAll, 0, std::vector<SolutionData>());
		MOCK_NON_CONST_METHOD(DeleteAll, 0, void());
		MOCK_NON_CONST_METHOD(DeleteById, 1, void(const misUID& id));
		MOCK_NON_CONST_METHOD(GetById, 1, SolutionData (const misUID& id));
		MOCK_NON_CONST_METHOD(InsertOrUpdate, 1, void (const SolutionData&));
		MOCK_NON_CONST_METHOD(PatientUidExists, 1, bool(const misUID& id));
	};
}
