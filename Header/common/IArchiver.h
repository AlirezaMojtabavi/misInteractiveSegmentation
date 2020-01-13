#pragma once

namespace parcast
{

	class IArchiver
	{
	public:
		virtual ~IArchiver() = default;
		virtual void Open(const std::string& archiveFilePath) = 0;
		virtual void Close() = 0;

		//- Archive given files list to a folder in the package
		virtual void ArchiveFiles(const std::string& destinationDirPath, const std::vector<std::string>& sourceDirPaths) const = 0;

		virtual void ArchiveFolderRecursive(const std::string& destinationDirPath, const std::string& sourceDirPaths) const = 0;

		virtual void ArchiveFolderContentsRecursive(
			const std::string& destinationDirPath, const std::string& sourceDirPath) const = 0;

		//- Extract files of a given folder in the archive file to outputPath
		virtual void ExtractFolderContentsRecursive(
			const std::string& sourceDirPath, const std::string& destinationDirPath) const = 0;
	};

}
