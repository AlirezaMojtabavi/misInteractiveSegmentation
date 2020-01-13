#pragma once

#include "ITextFileWriter.h"

MOCK_BASE_CLASS(MockTextFileWriter, ITextFileWriter)
{
	MOCK_NON_CONST_METHOD(Open, 2, void (const std::string& filePath, FileMode mode));
	MOCK_NON_CONST_METHOD(Write, 1, void (const std::string& data));
	MOCK_NON_CONST_METHOD(Close, 0, void ());
	MOCK_CONST_METHOD(IsOpen, 0, bool ());
};