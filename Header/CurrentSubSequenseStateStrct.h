#pragma once
#include <misResultMessageEnums.h>
#include <misSubSequenseGeneralStateEnums.h>

struct CurrentSubSequenseStateStrct
{
	std::string CurrentSubSequenseStateText;
	subSequenseGeneralStateEnums CurrentSubSequenseStateEnum;
	misResultMessageEnums ResultTypeEnum;
	std::string  ResultDescription;
};

