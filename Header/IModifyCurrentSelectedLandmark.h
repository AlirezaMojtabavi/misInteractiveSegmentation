#pragma once
#include <misLandmarkenums.h>

class IModifyCurrentSelectedLandmark
{
public:
	virtual ~IModifyCurrentSelectedLandmark() = default;
	virtual void Modify(int landmarkIndex, misLandmarkType landmarkType, bool modifiability)  = 0;
};
