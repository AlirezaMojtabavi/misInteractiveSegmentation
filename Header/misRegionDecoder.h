#pragma once
#include "misColorImage.h"

class misRegionDecoder
{
public:
	static ImageContainedDataType GetObjectValueIn16BitData(int index);
	static ImageContainedDataType GetObjectValue(int index, misRGObjectType objectType);
};
