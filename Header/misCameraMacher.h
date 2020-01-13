#pragma once
#include "misCamera.h"
class misCameraMacher
{

public:
	misCameraMacher();
	~misCameraMacher();
	static bool NearlyIsEqual(misCamera source, misCamera dest);
};

