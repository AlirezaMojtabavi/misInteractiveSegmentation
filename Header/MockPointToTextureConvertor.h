#pragma once

#include <vector.h>

#include <itkPoint.h>

MOCK_BASE_CLASS(MockPointToTextureConvertor, IPointToTextureConvertor)
{
	MOCK_CONST_METHOD(GetTexture, 0, GLuint ());
};