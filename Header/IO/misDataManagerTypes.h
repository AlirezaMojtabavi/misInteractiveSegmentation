#pragma once
#include "misStrctImageData.h"

struct misStrctImageDataRes
{
	std::string name ;
	int xRes;
	int yRes;
	int zRes;
	misStrctImageDataRes()
	{
		xRes=0;
		yRes=0;
		zRes=0;
	}
};

typedef std::vector<std::string> imageListTypdef;
