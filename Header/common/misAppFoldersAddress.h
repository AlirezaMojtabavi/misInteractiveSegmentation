#pragma  once

#include "misCommonHeader.h"
#include "misIOCheckUtilities.h"
#include "FileManager.h"



class  misAppFoldersAddress
{

public:
	misAppFoldersAddress(const std::string& startDirectory);

	std::string GetMainDataDirectory(void);
	std::string GetPatientName(void);
	std::string GetSolutionFolderName(void);
	std::string GetSolutionAddress(void);
	std::string GetSnapShotsAddress(void);
	std::string GetVideoRecordingAddress( void );
	std::string GetImagesAddress(void);
	std::string GetLogFileAddress( void );
	static std::string GetPacsTempDirectory()
	{
		return "D:/MIS Data/Biopsy/PACS_TempDir";
	}
	std::string GetRawDICOMImagesAddress( void );
	void Reset(void);
	void SetPatientName(std::string patientName);
	std::string GetPatientName() const;
	void SetSolutionFolderName(std::string solutionName);
	std::string GetMISDataDirectory() const;
protected:
	void SetMainSolutionDirectory(std::string path);

private:

	void        UpdateSolutionAddress(void);
	std::string MakeSubDirectoryAddress( std::string directoryName );

	std::string m_PatientName;

	std::string m_MainSolutionDirectory;
	std::string m_MISDataFolder;
	std::string m_SolutionFolderName;
	std::string m_CompleteSolutionFolderAddress;

	std::string m_ImageAddress;
	std::string m_SnapshotAddress;
	std::string m_VideoRecordingAddress;
	std::string m_LogFileFolder;
	std::string m_RawDICOMImages;
	parcast::FileManager m_FileManager;

};