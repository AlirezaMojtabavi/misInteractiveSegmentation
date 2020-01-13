#pragma warning(disable:4482)  // Disable warning messages

#pragma once
#include "igstkNDICommandInterpreter.h"


struct ToolExtraInformation
{

	igstk::NDICommandInterpreter::TXMarkerInfoType MarkersInformation[20];
	igstk::NDICommandInterpreter::TXToolInfoType ToolStatusInformation =
		igstk::NDICommandInterpreter::TXToolInfoType::Unset_Tool_Info;
	ToolExtraInformation();
	friend ostream& operator<<(ostream& os, const ToolExtraInformation& toolInfo);

};
