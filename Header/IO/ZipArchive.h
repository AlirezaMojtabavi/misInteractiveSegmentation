#pragma once

#include "IZipArchive.h"

namespace parcast
{

	class ZipArchive : public IZipArchive
	{
	public:
		ZipArchive();
		ZipArchive(const std::string& filePath);
		ZipArchive(const std::string& filePath, int flags);
		~ZipArchive();

		void Open(const std::string& filePath) override;
		void Open(const std::string& filePath, int flags) override;
		bool IsOpen() override;
		void Close() override;

		long long int GetLastError() override;

		void AddDirectory(const std::string& dirName) override;
		void AddFileFromLocalFile(const std::string& fileName, const std::string& localFileName) override;
		void AddFileFromLocalFile(const std::string& fileName, const std::string& localFileName, 
			long long int start, long long int length) override;

		long long int GetNumEntries() override;
		bool IsEntryDirectory(long long int index) override;
		std::string GetEntryName(long long int index) override;
		void ReadFileToLocalFile(long long int index, const std::string& localFileName) override;
		void ReadFileToLocalFile(long long int index, const std::string& localFileName, long long int length) override;

	private:
		zip_t* m_Archive;
		std::int32_t m_LastError;
	};

}