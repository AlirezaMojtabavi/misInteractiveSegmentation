#pragma once

#include "IArchiver.h"
#include "IFileManager.h"

namespace parcast
{

	class IZipArchive;

	class Archiver : public IArchiver
	{
	public:
		Archiver(std::shared_ptr<IZipArchive> zipArchive, std::shared_ptr<IFileManager> fileManager);
		void Open(const std::string& archiveFilePath) override;
		void Close() override;

		//- Archive given files list to a folder in the package
		void ArchiveFiles(const std::string& destinationDirPath, const std::vector<std::string>& sourceDirPaths) const override;

		//- Extract files of a given folder (and all its subfolders and their files) in the archive file to outputPath
		void ExtractFolderContentsRecursive(const std::string& sourceDirPath, const std::string& destinationDirPath) const override;

		//- Archive given localFolder to (and all its subfolders and their files) folder in the arhive file
		void ArchiveFolderContentsRecursive(const std::string& destinationDirPath, const std::string& sourceDirPath) const override;

		void ArchiveFolderRecursive(const std::string& destinationDirPath, const std::string& sourceDirPaths) const override;

	private:
		void AddDirectoryListToZipArchive(IFileManager::DirectoryList directoryList,
			boost::filesystem::path newDestinationPath) const;

		void CheckArchiveIsOpen() const;

		std::shared_ptr<IZipArchive> m_ZipArchive;
		std::shared_ptr<IFileManager> m_FileManager;

	};

}