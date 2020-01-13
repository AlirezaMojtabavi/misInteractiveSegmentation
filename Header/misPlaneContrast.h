#pragma once

#include "misWindowLevelStr.h"

enum misPlaneEnum
{
	FirstImage = 0,
	SecondImage = 1,
	UnSetPlane = 2
};

struct misPlaneIndexWinLevStr
{
	misWindowLevelStr	WinLev;
	misPlaneEnum		PlaneIndex;	
};
