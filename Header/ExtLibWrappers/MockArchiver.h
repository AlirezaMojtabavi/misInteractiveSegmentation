#pragma once

#include "IArchiver.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockArchiver, IArchiver)
	{
		MOCK_NON_CONST_METHOD(Open, 1, void(const std::string& archiveFilePath));
		MOCK_NON_CONST_METHOD(Close, 0, void());
		MOCK_CONST_METHOD(ArchiveFiles, 2, void(const std::string& destinationDirPath, const std::vector<std::string>& sourceDirPaths));
		MOCK_CONST_METHOD(ArchiveFolderRecursive, 2, void(const std::string& destinationDirPath, const std::string& sourceDirPaths));
		MOCK_CONST_METHOD(ArchiveFolderContentsRecursive, 2, void(const std::string& destinationDirPath, const std::string& sourceDirPath));
		MOCK_CONST_METHOD(ExtractFolderContentsRecursive, 2, void(const std::string& sourceDirPath, const std::string& destinationDirPath));
	};

}