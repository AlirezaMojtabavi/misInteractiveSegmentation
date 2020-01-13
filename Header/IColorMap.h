#pragma once
#include "misColorStruct.h"
class IColorMap
{
public:
	virtual ~IColorMap() = default;
	virtual misColorListTypedef GetColorMap() const = 0;
};
