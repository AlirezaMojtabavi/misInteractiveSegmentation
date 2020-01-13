#pragma once

#include "ITFILoader.h"

MOCK_BASE_CLASS(MockTFILoader, ITFILoader)
{
	MOCK_CONST_METHOD(LoadTFI, 1, misColorListTypedef (const std::string& fileName))
};