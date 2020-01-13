#pragma once
#include "ICheckVolumeRenderingSize.h"
MOCK_BASE_CLASS(MockCheckVolumeRenderingSize, ICheckVolumeRenderingSize)
{
	MOCK_CONST_METHOD(ICheckVolumeRenderingSize, 0, void());
};
