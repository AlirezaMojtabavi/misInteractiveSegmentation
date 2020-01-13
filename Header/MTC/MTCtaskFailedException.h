#pragma once

#include "MicronTrackerExceptions.h"

class MTCtaskFailedException :	public MicronTrackerExceptions
{
public:
	//MTCtaskFailedException(void);
	MTCtaskFailedException(mtCompletionCode CurrentErrorCode);
	~MTCtaskFailedException(void);
};

