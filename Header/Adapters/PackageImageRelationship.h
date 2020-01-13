#pragma once

namespace parcast
{

	struct PackageImageRelationship
	{
		std::string PackageUid;
		std::string ImageUid;
		double ImageOpacity;
		bool ImageVisibility;
	};

}
