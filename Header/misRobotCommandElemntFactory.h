#pragma once
#include "misRobotCommandElement.h"
#include <string>
class misRobotCommandElemntFactory
{
public:
	misRobotCommandElemntFactory(void);
	~misRobotCommandElemntFactory(void);
	static misRobotCommandElement*  CreateElement(std::string type);
};
