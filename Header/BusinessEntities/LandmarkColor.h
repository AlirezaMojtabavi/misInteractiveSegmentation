#pragma once
#include "ILandmarkColor.h"

namespace parcast
{
	class LandmarkColor : public ILandmarkColor
	{
	public:
		misDoubleColorStruct GetColor(misLandmarkType landmarkType, LANDMARKLABELSTAUS status) override;
	};
}
