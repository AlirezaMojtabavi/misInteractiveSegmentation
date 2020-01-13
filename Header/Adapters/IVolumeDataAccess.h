#pragma once

#include "VolumeData.h"

namespace parcast
{

	class IVolumeDataAccess
	{
	public:
		virtual ~IVolumeDataAccess() = default;
		virtual void Insert(const VolumeData& data) = 0;
		virtual std::vector<VolumeData> GetBySolutionUid(const std::string& uid) = 0;
	};
}