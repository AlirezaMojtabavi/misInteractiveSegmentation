#pragma once

#ifndef __MISADDTRACKERTOOLRW__
#define __MISADDTRACKERTOOLRW__

#include "misToolProperties.h"
 
using namespace System;
using namespace System::IO;
using namespace System::Xml;

ref class misAddTrackerToolRW
{
public:
	misAddTrackerToolRW(void);
	static void SaveTrackerToolData(misToolProperties ToolData,System::String^ Address);
	static misToolProperties ReadToolData(String^ Address);
};
#endif
