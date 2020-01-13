#pragma once

#include "ISegmentedImageDataAccess.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockSegmentedImageDataAccess, ISegmentedImageDataAccess)
	{
		MOCK_NON_CONST_METHOD(InsertOrUpdate, 1, void(const SegmentedImageData & inImageData));
		MOCK_CONST_METHOD(GetByImageUid, 1, SegmentedImageData(const std::string& imageUid));
		MOCK_CONST_METHOD(GetUidsBySolutionUid, 1, std::vector<std::string>(const std::string & solutionUid));
	};
}