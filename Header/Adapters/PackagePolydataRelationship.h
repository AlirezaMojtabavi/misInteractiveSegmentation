#pragma once
#include "DateTime.h"
namespace parcast
{
	struct PackagePolyDataRelationship
	{
		std::string ImageContainedPolyDataUid;
		std::string PackageUid;
		std::string ParentImageUid;
	};

}