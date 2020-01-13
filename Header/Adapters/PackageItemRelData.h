#pragma once
namespace parcast
{
	struct PackageItemRelData
	{
		std::string PackageUid;
		std::string ItemUid;
		bool IsUsable;
		bool Visibility2D;
		bool Visibility3D;
		double Opacity2D;
		double Opacity3D;
	};
}
