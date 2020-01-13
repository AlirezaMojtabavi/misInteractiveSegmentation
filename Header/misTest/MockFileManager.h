#pragma once
#include "IFileManager.h"

namespace parcast
{
	MOCK_BASE_CLASS(MockFileManager, IFileManager)
	{
		MOCK_CONST_METHOD(Exists, 1, bool(const std::string& filePath));
		MOCK_CONST_METHOD(RemoveFile, 1, void (const std::string& filePath));
		MOCK_CONST_METHOD(CreateDirectories, 1, void(const std::string& path));
		MOCK_CONST_METHOD(GetDirectoryList, 1, DirectoryList(const std::string& path));
		MOCK_CONST_METHOD(GetAllFilesInDir, 2, std::vector<std::string>(const std::string &dirPath, const std::vector<std::string> dirSkipList));
	};
}
