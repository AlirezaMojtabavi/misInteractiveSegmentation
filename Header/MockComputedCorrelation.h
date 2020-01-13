#pragma once

#include "IComputedCorrelation.h"

MOCK_BASE_CLASS(MockComputedCorrelation, IComputedCorrelation)
{
	MOCK_CONST_METHOD(GetStatus, 0, Status ());
	MOCK_CONST_METHOD(IsValid, 0, bool ());
	MOCK_CONST_METHOD(GetTransform, 0, TransformConstPtr ());
	MOCK_CONST_METHOD(GetLastModifiedTime, 0, TimePointType ());
};