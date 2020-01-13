#pragma once

#include "misCopyFile.h"
#include "misDIRReader.h"
#include "IO/misDicomPreoperation.h"
#include "misImageIndexData.h"

// The misDICOMImageLoader class provides means for building patient data tree and reading image (as VTK 3D image objects)
// series as asynchronous operations. It also reports its instantaneous operation status and progress value. The client code can 
// stop the operation after it has been started through calls to StartAnalyzeDirectoryToBuildPatientTree() or 
// StartLoadingSeries().
// After any of the two operations start, the loader goes into the working state, and its current activity is accordingly update.
// The progress value is also continually updated from 0 to 1. During the operation, if any errors occur, the operation stops and
// the status is updated. When the operation is completed successfully, the status changes to finished. 
class misDICOMImageLoader
{
public:
	// The Status enumeration defines all the states in which the misDICOMImageLoader object can be at any time. 
	enum Status
	{
		STATUS_NOT_STARTED	// The initial state of the loader right after creation
		, STATUS_WORKING	// Loader is performing some activity
		, STATUS_CANCELLED	// Loader has been successfully stopped after receiving a cancel request
		, STATUS_FINISHED	// Loader has successfully finished its last operation.
		, STATUS_ERROR	// Loader encountered an error during the last operation and the operation was abnormally terminated.
	};

	// The Activity enumeration defines the activities in which the misDICOMImageLoader can engage at any time
	enum Activity
	{
		ACTIVITY_NONE	// The loader has not performed any jobs yet
		, ACTIVITY_PROCESSING_SERIES	// The loader is reading an image series and creating the 3D image.
		, ACTIVITY_BUILDING_TREE	// The loader is building the patient data tree
	};

	// Creates and initializes the misDICOMImageLoader object using values retrieved from persistent application settings.
	misDICOMImageLoader(void);

	// Destroys the misDICOMImageLoader after disposing of allocated resources.
	~misDICOMImageLoader(void);

	// Starts analysis of the specified directory to build the patient data tree in a separate thread and returns immediately.
	void StartAnalyzeDirectoryToBuildPatientTree(std::string directory);

	//analysis of the specified directory to build the patient data tree.
	PatientsContainerViewingTypdef AnalyzeDirectoryToBuildPatientTree(const std::string& directory);

	// Starts loading of the series specified using the given index in a separate thread and returns immediately.
	void							StartLoadingSeries(misImageIndexData add);

	// Gets the patient data tree after the directory analysis has been successfully finished.
	PatientsContainerViewingTypdef GetAsyncPatientTree();
	// Gets the patient data tree after the directory analysis has been successfully finished.
	PatientsContainerViewingTypdef GetPatientTree();

	// Gets the image series UID which can be used to test if a series has been already processed.
	misUID							GetSeriesUID(misImageIndexData imageIndex);

	// Gets the 2D image specified using the given index data. 
	vtkImageData*					Get2DImage(misImageIndexData add);

	// Gets the 2D image specified using the given image file path. 
	vtkImageData*					Get2DImage(std::string imagePath);

	// Used in tests exclusively: creates an image index data using the specified tree, patient index, study index and series index.
	misImageIndexData				GetImageIndexData(
		PatientsContainerViewingTypdef tree, int patientInx, int studyInx, int SeriInx);

	// While the loader is in the working state (busy performing any of the operations), calling RequestStop() will notify the 
	// loader that it must stop the operation at earliest possibility.
	void							RequestStop();

	// Copies files related to the images read so far to the to Patient folder preserving the directory structure.
	bool							CopyRawDICOMImages();

	// Gets whether the DICOMDIR file exists alongside of the image folder. Use this if you need to prompt a warning after an 
	// an attempt to build the patient data tree.
	bool							ExistDICOMDIRFile();

	// Gets the current status of the loader. See Status enumeration.
	Status							GetStatus();

	// Gets the last operation performed by the loader (or the current one if currently working). See Activity enumeration.
	Activity						GetLastActivity();

	// Gets the amount of progress made through the current operation as a value between 0 and 1.
	double							GetProgressValue();

	// Gets the loaded series when the StartLoadingSeries() leads to the finished status.
	std::unique_ptr<misImage> GetLoadedSeries();

	// Set m_3DImage to NULL. It must be called  to prevent of memory leak.
	void							Release3DImage();
	// function for loading series.
	std::unique_ptr<misImage> LoadSeries(const misImageIndexData& index);
	std::string GetPatientPosition();
	float* GetImageOrientationPatient();
private:
	// Creates a directory under the patient data temp directory to hold a copy of the original data (if copying from CD)
	void	PrepareDirectoryToCopyData();

	// Determines whether the source is an optical drive.
	void	IsSourceOpticalDrive(std::string source);

	// Prepare the list of image file paths by converting relative paths to absolute.
	void	PrepareUploadedImagesListToExport(std::vector<std::string> imageList);

	// If the data is compressed, creates a corresponding folder in a temp directory under the patient directory to 
	// hold decompressed data.
	void	PrepareDirectoryToUncompressData();

	// Creates the temporary directory under patient data directory.
	bool	PreparedTemporaryDataDirectory();

	// Creates the directory tree in the destination (patient data directory) according to the directory structure of the source.
	bool	CreateSubDirectories(std::string destination, std::string source);

	// Calculates the overall progress when building the patient tree.
	double	GetProgressBarValueWhileBuildingPatientTree();

	// Calculates the overall progress when processing data series.
	double	GetProgressBarValueWhileProcessingSerie();

	// Returns the value of m_CDIndex as a string.
	std::string	ConvertCDIndexToString();

	// Thread start function for directory analysis. Calls DoAnalyzeDirectory on the object.
	static unsigned int _stdcall AnalyzeDirectoryThreadStart(void *param);

	// Thread start function for loading series. Calls DoAnalyzeDirectory on the object.
	static unsigned int _stdcall LoadSeriesThreadStart(void *param);

	// Performs the actual directory analysis operation.
	void		DoAnalyzeDirectory();

	// Performs the actual load series operation.
	void		DoLoadSeries();

	// Copies the data series from the optical drive to patient directory temp folder.
	std::vector<std::string> CopySeries(std::vector<std::string> imageList);

	// Decompresses the data if compressed and copies the extracted files to the corresponding folder in patient temp directory.
	std::vector<std::string> PreparedDataInCaseCompressed(std::vector<std::string> imageList);

	// Creates a VTK 3D image object using the specified list of image files.
	std::unique_ptr<misImage> Get3DImage(std::vector<std::string> imageList);

	// Disposes of the operation thread. Called before starting of a new thread and in the destructor.
	void DisposeOperationThread();

	misDIRReader*			m_pDIRReader;
	misDicomPreoperation	m_DicomUncompressor;
	misCopyFile				m_fileSys;	// Used for copying files and directories and other file operations.
	misSerieCheckValidation m_SeriesChecker;	// Used for checking different image properties for validity.
	bool m_CopyPatientCDOnHard;	// Corresponds to the application setting of the same name.
	bool m_CheckDataRepresentation;	// Corresponds to the application setting of the same name.
	bool m_SourceIsAnOpticalDrive;	// See IsSourceOpticalDrive()
	bool m_DICOMDIRWasFound;	// Determines whether the DICOMDIR file was found. See ExistDICOMDIRFile()
	bool m_CancelRequested;	// Holds a value determining whether a cancel request has been issued. See RequestStop().
	int	 m_CDIndex;	// Used if patient data is stored on more than one disc to differentiate amongst them.
	Status  m_Status;	// See GetStatus().
	Activity m_LastActivity;	// See GetLastActivity().
	double		m_ProgressValue;	// See GetProgressValue().
	std::string m_DataPathOnHard;	// Local path on the hard drive where patient data directory.
	std::string m_DestinationToCopy;	// Local directory path within patient directory where original data is stored.
	std::string m_InitialSourcePath;	// The source directory to be analyzed. See StartAnalyzeDirectoryToBuildPatientTree()
	std::string m_PatientPosition = "";
	misImageIndexData m_ImageIndexData;	// The image series index to be loaded. See StartLoadingSeries()
	std::unique_ptr<misImage>	m_3DImage;	// See Get3DImage()
	std::vector<std::string>	m_UploadedImagesListToExport;	// List of image series loaded so far.
	PatientsContainerViewingTypdef m_PatientContainerViewing;	// Patient tree structure
	HANDLE m_OperationThread;	// The thread handle in charge of performing the operations asynchronously.
	float* m_ImageOrientationPatient;
};

