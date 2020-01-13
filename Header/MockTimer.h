#pragma once

#include "ITimer.h"

MOCK_BASE_CLASS(MockTimer, ITimer)
{
	MOCK_NON_CONST_METHOD(Start, 0, void ());
	MOCK_NON_CONST_METHOD(Stop, 0, void ());
	MOCK_NON_CONST_METHOD(Reset, 0, void ());
	MOCK_CONST_METHOD(GetTime, 0, double ());
};