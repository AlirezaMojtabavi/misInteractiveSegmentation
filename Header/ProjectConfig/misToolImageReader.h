#pragma once

#include "misToolImageStrct.h"

class misToolImageReader
{
public:
	misToolImageReader(void);
	~misToolImageReader(void);

	static misToolImageStrct ToolImageReader(std::string imagePath);
};
