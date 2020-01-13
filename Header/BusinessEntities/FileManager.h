#pragma once

#include "IFileManager.h"

namespace parcast
{

	class FileManager : public IFileManager
	{
	public:
		bool Exists(const std::string& filePath) const override;
		void RemoveFile(const std::string& filePath) const override;
		void CreateDirectories(const std::string& path) const override;
		DirectoryList GetDirectoryList(const std::string& path) const override;

		virtual std::vector<std::string> GetAllFilesInDir(const std::string &dirPath, const std::vector<std::string> dirSkipList = {}) const override;

	};

}

