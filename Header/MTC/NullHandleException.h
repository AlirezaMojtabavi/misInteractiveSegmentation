#pragma once

#include "MicronTrackerExceptions.h"

class NullHandleException :	public MicronTrackerExceptions
{
public:
	NullHandleException(void);
	~NullHandleException(void);
};

