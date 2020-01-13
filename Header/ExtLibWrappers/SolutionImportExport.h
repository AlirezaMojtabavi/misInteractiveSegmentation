#pragma once

#include "ISolutionImportExport.h"
#include "ISegmentedImageDataAccess.h"

class IDatasetManager;

namespace parcast
{

	class IArchiver;
	class IDatabaseImportExport;
	class IFileManager;
	class IImageDataAccess;
	class IDataBaseConnection;

	class SolutionImportExport : public ISolutionImportExport
	{
	public:
		SolutionImportExport(
			std::shared_ptr<IFileManager> fileManager,
			std::shared_ptr<IDatabaseImportExport> dataBaseImportExport,
			IDatasetManager* datasetManager,
			std::shared_ptr<IImageDataAccess> imageDataAccess,
			std::shared_ptr<ISegmentedImageDataAccess> segmentedImageDataAccess,
			std::shared_ptr<IArchiver> archiver,
			const std::string& temporaryDbFilePath,
			const std::string& binaryImagesPath,
			std::shared_ptr<IDataBaseConnection> dbConnection);

		void Export(const std::string& path) const override;
		void Import(const std::string& path) const override;
		void SetAuxiliarySolutionFolder(std::string path) override;

	private:
		const std::string DatabaseFolderInArchiveFile = "SqliteDatabaseFile";
		const std::string BinaryImageFolderInArchiveFile = "BinaryImages";
		const std::string AuxiliarySolutionFolderInArchiveFile = "AuxiliarySolutionFolder";

		void RemoveFileIfExists(const std::string& filePath) const;
		std::vector<std::string> CreateBinaryImageFileList() const;

		std::vector<std::string> CreateBinarySegmentedImageFileList() const;
		std::shared_ptr<IFileManager> m_FileManager;
		std::shared_ptr<IDatabaseImportExport> m_DatabaseImportExport;
		std::shared_ptr<IImageDataAccess> m_ImageDataAccess;
		std::shared_ptr<ISegmentedImageDataAccess> m_SegmentedImageDataAccess;

		std::shared_ptr<IArchiver> m_Archiver;
		std::shared_ptr<IDataBaseConnection> m_DbConnection;
		IDatasetManager* m_DatasetManager;
		std::string m_BinaryImagesPath;
		std::string m_TemporaryDbFilePath;
		std::string m_AuxiliarySolutionFolder;
	};

}
