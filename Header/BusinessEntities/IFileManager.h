#pragma once

namespace parcast
{

	enum class DirectoryEntryType { File, Directory };

	struct DirectoryEntry
	{
		std::string Path;
		DirectoryEntryType Type;
	};

	class IFileManager
	{
	public:
		using DirectoryList = std::vector<DirectoryEntry>;

		virtual bool Exists(const std::string& filePath) const = 0;
		virtual void RemoveFile(const std::string& filePath) const = 0;
		virtual void CreateDirectories(const std::string& path) const = 0;
		virtual DirectoryList GetDirectoryList(const std::string& path) const = 0;
		virtual std::vector<std::string> GetAllFilesInDir(const std::string &dirPath, const std::vector<std::string> dirSkipList = {}) const = 0;

		virtual ~IFileManager() = default;
	};

}