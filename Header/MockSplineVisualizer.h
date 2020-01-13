#pragma once

#include "ISplineVisualizer.h"

MOCK_BASE_CLASS(MockSplineVisualizer, ISplineVisualizer)
{
	MOCK_NON_CONST_METHOD(AddSplineWidgetToAxialViewer, 1, bool(const SplinePoints& splinePoints));
	MOCK_NON_CONST_METHOD(LockSpline, 0, bool());
	MOCK_NON_CONST_METHOD(NewSpline, 0, void());
	MOCK_NON_CONST_METHOD(UndoSpline, 0, bool());
	MOCK_NON_CONST_METHOD(ChangeWidgetVisibility, 1, void(bool visibility));
	MOCK_NON_CONST_METHOD(GetSplinePoints, 0, SplinePoints());

};