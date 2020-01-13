#pragma once
#include "ImageData.h"
#include "IImageDataAccess.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockImageDataAccess,IImageDataAccess)
	{
		MOCK_NON_CONST_METHOD(InsertOrUpdate, 1, void(const ImageData & inImageData));
		MOCK_CONST_METHOD(GetBySolutionUid, 1, std::vector<ImageData>(const std::string& solutionUid));
		MOCK_NON_CONST_METHOD(Update, 1, void(const ImageData & inImageData));
		MOCK_NON_CONST_METHOD(Insert, 1, void(const ImageData & inImageData));
		MOCK_NON_CONST_METHOD(Delete, 2, void(const std::string& FK_SolutionUid, const std::string& ImageUid));
		MOCK_CONST_METHOD(GetUidsBySolutionUid, 1, std::vector<std::string> (const std::string& solutionUid));
	};
}
