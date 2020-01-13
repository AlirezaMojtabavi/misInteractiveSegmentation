#pragma once
#include "VirtualKeyStruct.h"
class EventEnumeration
{
public:
	static EventEnumeration* New(){return new EventEnumeration();}
	~EventEnumeration(void);

	CommandEnum CommandGenerationVirtualKey(int	regionID, std::string subprocedureName);

private:
	EventEnumeration(void);
};
