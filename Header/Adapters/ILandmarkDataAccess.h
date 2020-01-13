#pragma once

#include "LandmarkData.h"

namespace parcast
{
	class ILandmarkDataAccess
	{
	public:
		virtual void DeleteByPackageUid(const std::string& uid) = 0;
		virtual void Insert(const LandmarkData& data) = 0;
		virtual std::vector<LandmarkData> GetByPackageUid(const std::string& Uid) = 0;
	};
}
