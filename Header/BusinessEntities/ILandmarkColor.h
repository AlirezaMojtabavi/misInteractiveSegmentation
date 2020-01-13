#pragma once
#include "misLandmarkenums.h"
#include "misStrctColorData.h"

namespace parcast
{

	class ILandmarkColor
	{
	public:
		virtual ~ILandmarkColor() = default;
		virtual misDoubleColorStruct GetColor(misLandmarkType landmarkType, LANDMARKLABELSTAUS status) = 0;
	};

}
