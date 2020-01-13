#pragma once
namespace parcast
{
	struct VolumeVisibility
	{
		std::string Viewing;
		std::string VolumeUid;
		bool Visibility2D;
		bool Visibility3D;
		double Opacity2D;
		double Opacity3D;
	};
}

