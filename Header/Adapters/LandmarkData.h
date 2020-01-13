#pragma once

#include "BusinessEntities\Point.h"

namespace  parcast
{

	struct LandmarkData
	{
		std::string LandmarkUid;
		std::string PackageUid;
		Point<double, 3> Position;
		long long int Type;
	};

}