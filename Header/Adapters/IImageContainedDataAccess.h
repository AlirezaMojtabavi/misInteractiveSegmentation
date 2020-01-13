#pragma once

#include "ImageContainedData.h"

namespace parcast
{

	class IImageContainedDataAccess
	{
	public:
		virtual ~IImageContainedDataAccess() = default;
		virtual void Insert(const ImageContainedData& data) = 0;
		virtual std::vector<ImageContainedData> GetBySolutionUid(const std::string& uid) = 0;
	};
}