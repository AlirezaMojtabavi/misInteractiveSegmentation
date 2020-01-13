#pragma once

#include "ImageData.h"

namespace parcast
{

	class IImageDataAccess
	{
	public:

		virtual void InsertOrUpdate(const ImageData & inImageData) = 0;
		virtual std::vector<ImageData> GetBySolutionUid(const std::string& solutionUid) const = 0;
		virtual std::vector<std::string> GetUidsBySolutionUid(const std::string& solutionUid) const = 0;
		virtual void Delete(const std::string& FK_SolutionUid, const std::string& ImageUid) = 0;

		virtual ~IImageDataAccess() { }
	};

}
