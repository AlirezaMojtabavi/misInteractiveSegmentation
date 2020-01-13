#pragma once
#include "misColorStruct.h"

class  IColorMapGenerator
{
public:
	virtual ~IColorMapGenerator() = default;;
	virtual misColorListTypedef GetColorMap(bool useDefaultColor, const misColorStruct& objectColor) const = 0;
	virtual void SetViewingThreshold(bool useDefaultThreshold, double minThreshold) = 0;
	virtual void SetMinThreshold(double) = 0;
	virtual void SetMaxThreshold(double) = 0;
};
