#pragma once

#include "IPanoramicCoordinatesConverter.h"

MOCK_BASE_CLASS(MockPanoramicCoordinatesConverter, IPanoramicCoordinatesConverter)
{
	MOCK_NON_CONST_METHOD(SetImageCoordinates, 3, void (double x, double y, double z));
	MOCK_NON_CONST_METHOD(SetPanoramicCoordinates, 3, void (double s, double z_p, double n));
	MOCK_CONST_METHOD(GetImageCoordinates, 3, void (double &x, double &y, double &z));
	MOCK_CONST_METHOD(GetPanoramicCoordinates, 3, void (double &s, double &z_p, double &n));
	MOCK_CONST_METHOD(GetCurrentSplineLength, 0, double());
	MOCK_CONST_METHOD(EvaluateCurrentSpline, 1, PointType(double));
	MOCK_CONST_METHOD(GetCurrentNormalVector, 0, VectorType());
	MOCK_CONST_METHOD(GetCurrentTangentialVector, 0, VectorType());
};