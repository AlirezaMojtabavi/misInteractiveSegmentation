#pragma once
//                        *****************************************
// Important Note : this header is not allowed to add any header from itk or VTK
//                        *****************************************

#include <string>
struct misRobotCommandStr
{
	std::string  CommandString;
	bool         AutomaticDispatchCommand;
	bool         AutoFillMessage;

	void Reset(void)
	{
		CommandString = "";
		AutomaticDispatchCommand = false;
		AutoFillMessage          = false;
	};

	misRobotCommandStr()
	{
		Reset();
	}
};