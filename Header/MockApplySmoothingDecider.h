#pragma once

#include "IAppySmoothingDecider.h"

MOCK_BASE_CLASS(MockApplySmoothingDecider, IApplySmoothingDecider)
{
	MOCK_CONST_METHOD(GetAdaptiveHistoryLength, 0, signed int());
	MOCK_NON_CONST_METHOD(SetAdaptiveHistoryLength, 1, void(int val));
	MOCK_NON_CONST_METHOD(SetTranslationTolerance, 1, void(double val));
	MOCK_NON_CONST_METHOD(SetRotationTolerance, 1, void(double val));
	MOCK_NON_CONST_METHOD(AppendTransform, 2, void(const tgt::Matrix4d& matrix, double time));
	MOCK_NON_CONST_METHOD(SetHistoryLength,1, void(int val));
	MOCK_NON_CONST_METHOD(SetTimeForCheckFixedOrMoving, 1, void(double val));
	MOCK_NON_CONST_METHOD(SetTimeFixingKernel,1, void(double val));
};

