#pragma once

#include "PanoramicData.h"

namespace parcast
{
	class IPanoramicDataAccess
	{
	public:

		virtual ~IPanoramicDataAccess() {}
		virtual void InsertOrUpdate(const PanoramicData& panoramicData) = 0;
		virtual std::vector<PanoramicData> GetByImageUid(const std::string& imageUid) = 0;
	};
}


