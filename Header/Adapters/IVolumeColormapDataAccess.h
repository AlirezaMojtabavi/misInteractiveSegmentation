#pragma once
#pragma once
#include "VolumeColormap.h"
 
namespace parcast
{
	class IVolumeColormapDataAccess
	{
	public:
		virtual ~IVolumeColormapDataAccess() = default;
		virtual void Insert(const VolumeColormap& data) = 0;
		virtual std::vector<VolumeColormap> GetByVolumeUid(const std::string& uid) const = 0;
	};
}

