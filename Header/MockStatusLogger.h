#pragma once

#include "IStatusLogger.h"

MOCK_BASE_CLASS(MockStatusLogger, IStatusLogger)
{
	MOCK_NON_CONST_METHOD(Start, 0, void ());
	MOCK_CONST_METHOD(IsStarted, 0, bool ());
	MOCK_NON_CONST_METHOD(Stop, 0, void ());
	MOCK_CONST_METHOD(UpdateLogs, 0, void ());
};