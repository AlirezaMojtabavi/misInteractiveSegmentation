#pragma once

#include "ICoordinateSystemRenderer.h"

MOCK_BASE_CLASS(MockCoordinateSystemRenderer, ICoordinateSystemRenderer)
{
	MOCK_NON_CONST_METHOD(Render, 0, void());
	MOCK_NON_CONST_METHOD(SetCoordinateSystem, 1, void(const std::string&  coordinateSytem));
	MOCK_NON_CONST_METHOD(SetRefrenceCoordinate, 1, void(const  std::string&  coordinateSytem));
	MOCK_NON_CONST_METHOD(RenderingOn, 0, void());
	MOCK_NON_CONST_METHOD(RenderingOff, 0, void());
	MOCK_NON_CONST_METHOD(SetColor, 3, void(float r, float g, float b));
};
