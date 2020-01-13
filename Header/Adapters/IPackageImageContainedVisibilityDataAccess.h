#pragma once

#include "ImageContainedVisibility.h"

namespace parcast
{

	class IPackageImageContainedVisibilityDataAccess
	{
	public:
		~IPackageImageContainedVisibilityDataAccess() = default;

		virtual void Insert(const parcast::ImageContainedVisibility& data) = 0;
		virtual std::vector<parcast::ImageContainedVisibility> GetByImageContainedUid(const std::string& uid) const = 0;
	};

}