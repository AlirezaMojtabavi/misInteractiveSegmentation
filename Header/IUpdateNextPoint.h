#pragma once
#include "misLandmarkenums.h"

class IUpdateNextPoint
{
public:
	virtual ~IUpdateNextPoint() = default;
	virtual int Update(int& currentSelectedLandmarkIndex, misLandmarkType lndType,
	                   bool& setRegistrationPointRequestSent) = 0;
};
