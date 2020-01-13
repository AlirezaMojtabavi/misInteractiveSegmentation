#pragma once
#include "misSTRCT.h"

namespace parcast
{
	class CreateLandmark
	{
	public:
		static misLandmarkPointStrct Create(double x, double y, double z, misLandmarkType type = BoneLandmark)
		{
			misLandmarkPointStrct landmark;
			landmark.position[0] = x;
			landmark.position[1] = y;
			landmark.position[2] = z;
			landmark.pointType = type;
			return landmark;
		}
	};
}
