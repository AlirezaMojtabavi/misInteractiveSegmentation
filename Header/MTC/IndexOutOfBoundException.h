#pragma once

#include "MicronTrackerExceptions.h"

class IndexOutOfBoundException :public MicronTrackerExceptions
{
public:
	IndexOutOfBoundException(void);
	~IndexOutOfBoundException(void);
};

