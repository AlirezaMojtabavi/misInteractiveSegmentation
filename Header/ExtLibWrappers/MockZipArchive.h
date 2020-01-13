#pragma once
#include "IZipArchive.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockZipArchive, IZipArchive)
	{
		MOCK_NON_CONST_METHOD(Open, 2, void(const std::string& filePath, int flags), Open_State);
		MOCK_NON_CONST_METHOD(Open, 1, void(const std::string& filePath));
		MOCK_NON_CONST_METHOD(IsOpen, 0, bool());
		MOCK_NON_CONST_METHOD(Close, 0, void());
		MOCK_NON_CONST_METHOD(GetLastError, 0, long long int());
		MOCK_NON_CONST_METHOD(AddDirectory, 1, void(const std::string& dirName));
		MOCK_NON_CONST_METHOD(AddFileFromLocalFile, 2, void(const std::string& fileName, const std::string& localFileName));

		MOCK_NON_CONST_METHOD(AddFileFromLocalFile, 4,
			void(const std::string& fileName, const std::string& localFileName, long long int start, long long int length),
			AddFileFromLocalFile_Partial);

		MOCK_NON_CONST_METHOD(GetNumEntries, 0, long long int());
		MOCK_NON_CONST_METHOD(IsEntryDirectory, 1, bool(long long int index));
		MOCK_NON_CONST_METHOD(GetEntryName, 1, std::string(long long int index));

		MOCK_NON_CONST_METHOD(ReadFileToLocalFile, 2, void(long long int index, const std::string& localFileName));

		MOCK_NON_CONST_METHOD(ReadFileToLocalFile, 3,
			void(long long int index, const std::string& localFileName, long long int length), ReadFileToLocalFile_Partial);

	};
}
