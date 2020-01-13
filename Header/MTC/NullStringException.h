#pragma once

#include "MicronTrackerExceptions.h"

class NullStringException :	public MicronTrackerExceptions
{
public:
	NullStringException(void);
	~NullStringException(void);
};

