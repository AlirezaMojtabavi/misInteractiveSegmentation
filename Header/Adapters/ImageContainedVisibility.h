#pragma once
namespace parcast
{
	struct ImageContainedVisibility
	{
		std::string packgeUid;
		std::string ImageContainedPolyDataUid;
		std::string ThreeDModelUid;
		bool Visibility2D;
		bool Visibility3D;
		double Opacity2D;
		double Opacity3D;
	};
}