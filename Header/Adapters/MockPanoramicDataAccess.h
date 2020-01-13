#pragma once

#include "IPanoramicDataAccess.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockPanoramicDataAccess, IPanoramicDataAccess)
	{
		MOCK_NON_CONST_METHOD(InsertOrUpdate, 1, void(const PanoramicData& panoramicData));
		MOCK_NON_CONST_METHOD(GetByImageUid, 1, std::vector<PanoramicData>(const std::string& imageUid));
		
	};

}
