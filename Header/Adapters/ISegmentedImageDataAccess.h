#pragma once
#include "segmentedImageData.h"

namespace parcast
{

	class ISegmentedImageDataAccess
	{
	public:

		virtual void InsertOrUpdate(const SegmentedImageData & inImageData) = 0;
		virtual SegmentedImageData GetByImageUid(const std::string& imageUid) const = 0;
		virtual std::vector<std::string> GetUidsBySolutionUid(const std::string & solutionUid) const = 0;


		virtual ~ISegmentedImageDataAccess() { }
	};

}