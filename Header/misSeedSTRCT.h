#pragma once
#ifndef misSeedSTRCT_H
#define misSeedSTRCT_H

#include "misLandmarkenums.h"

enum ColorOfSeed
{
	Green=0,
	Blue
};

struct misSeedSTRCT
{
	typedef itk::Image< float , 3 > ImageType;
	ImageType::IndexType     seedposition;
	misLandmarkType  seedtype;
	float realposition[3];
    ColorOfSeed  seedcolor;
};

#endif  