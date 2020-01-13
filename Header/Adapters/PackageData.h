#pragma once

#include "DateTime.h"

namespace parcast
{

	struct PackageData
	{
		std::string SolutionUid;
		std::string PackageUid;
		std::string PackageName;
		long long int ObjectType;
	};

}
