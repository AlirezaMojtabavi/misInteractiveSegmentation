#pragma once
#include "misColorStruct.h"
// these color map keys copied from 3d Slicer MRIT2 color map
class IMRIColoredColorMap
{
public:
	virtual misColorListTypedef GetColorList() const = 0;

};