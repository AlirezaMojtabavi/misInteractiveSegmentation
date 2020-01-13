#pragma once
#include "misColorStruct.h"
// This class reads an XML file contains trans function and return it as a transfuncIntensity class.
class ITFILoader
{
public:
	// See class definition
	virtual misColorListTypedef LoadTFI(const std::string& fileName) const = 0;
	virtual ~ITFILoader() { };
};