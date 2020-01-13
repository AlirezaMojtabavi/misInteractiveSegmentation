#pragma once

namespace parcast
{

	class IZipArchive
	{
	public:
		virtual ~IZipArchive() = default;

		virtual void Open(const std::string& filePath) = 0;
		virtual void Open(const std::string& filePath, int flags) = 0;
		virtual bool IsOpen() = 0;
		virtual void Close() = 0;
		virtual long long int GetLastError() = 0;
		virtual void AddDirectory(const std::string& dirName) = 0;
		virtual void AddFileFromLocalFile(const std::string& fileName, const std::string& localFileName) = 0;
		virtual void AddFileFromLocalFile(const std::string& fileName, const std::string& localFileName,
			long long int start, long long int length) = 0;

		virtual long long int GetNumEntries() = 0;
		virtual bool IsEntryDirectory(long long int index) = 0;
		virtual std::string GetEntryName(long long int index) = 0;
		virtual void ReadFileToLocalFile(long long int index, const std::string& localFileName) = 0;
		virtual void ReadFileToLocalFile(long long int index, const std::string& localFileName, long long int length) = 0;
	};

}
