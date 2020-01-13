#pragma once

#include "ImageContainedProperties.h"

namespace parcast
{

	class IImageContainedPropertiesDataAccess
	{
	public:
		virtual ~IImageContainedPropertiesDataAccess() = default;

		virtual void Insert(const ImageContainedProperties& data) = 0;
		virtual std::vector<ImageContainedProperties> GetByImageContainedUid(const std::string& uid) const = 0;
	};

}

