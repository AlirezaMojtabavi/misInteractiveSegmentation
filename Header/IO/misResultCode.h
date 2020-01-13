#ifndef _misResultCode_h
#define _misResultCode_h

class misResultCode
{
public:
	enum ResultIds {
		NoError = 0,
		OkFileXXXFileReadSuccessfully = 100,
		ErFileXXXNotAbleToWrite,
		ErUnAvailableFolder,
		ErUnableTocreateNewFolder,
		ErFileXXXFileNameIsEmpty,
		ErFileXXXFileNotFoundError, 
		ErFileXXXCannotOpenFileError,
		ErFileXXXUnrecognizedFileTypeError,
		ErFileXXXPrematureEndOfFileError,
		ErFileXXXFileFormatError,
		ErFileXXXNoFileNameError,
		ErFileXXXOutOfDiskSpaceError,
		ErFileXXXAddingWithSameUID,
		OkUpdateUIDXXXUpdateSuccessfully = 200,
		ErUpdateUIDXXXUpdateError,
		OkUpdateListNameXXXUpdateListNameSuccessfuly = 210,
		ErUpdateListNameXXXInstanceNumberIsNotUpdated,
		ErUpdateListNameXXXInstanceNumberIsNotUpdatable,
		ErUpdateListNameXXXLeadingToError, 
		OkMemoryXXXMemoryAllocationSuccessfully =300,
		ErMemoryXXXNotallocatingError,
		ErXXXUnknownError = 10000,
		UserResult = 40000,
		NotCompletedYet,
		ErUnableToLoadPatientSolutionXmlFile = 1000,
		ErNotAnOriginalPatientSolutionFile = 1001,
		ErFileDoseNotExist = 1002,
		ErHybridPackagesHasNoChild = 1003,
		ErNoHybridPackageMatchFound = 1004,
		ErPolyDataExists = 1005,
		ErUnableToReadHybridPackage_NullImageData = 1006,
		ErUnableToReadHybridPackage_NullPolyDatas = 1007,
		ErDuplicatedpackage,
		ErImageNonExist,
		ErPolyDataNotExist,
		ErNotAbalieToAddSomeImgagesforHP,
		ErNoValidPointer,
		ErOnlyOneImageForHPIsValid,
		ErDifferenetParrentForHP,
		ErNotAvailabeCorrelation,
		ErUnableToFindInList,
		ErUnableToDeleteFromList,
		ErUnableToAddIntheList,
		ErUnableToReadVTKImageFile,
		ErInValidIdInTheList,
		ErEmptyPointer,
		ErEmptyList,
        ErEmptyObjectUID,
		ErEmptyParrentImageUID,
		ErDifferentImageUID,
		ErDuplicatedObjectNotPermitable,
		ErUnableTOAddInList,
		ErMaximunValidSize,
		ErUnEqualInput,
		ErIncompleteFuctionYet,
		ErInacceptedImageNumber,
		ErInaccptedImageComponent,
		ErEmptySolutionUID,
		ErInvalidDatabase,
		WrEmptyList,
		ErfMRIWithNoMRI
	  };


	//BTX
  // all the currently defined Result codes
  // developers can use -- vtkResultCode::UserResult + int to
  // specify their own Results. 
  //*****************************************************************
  //                                 ::Important Note::
  // if this list is adjusted, be sure to adjust misResultCodeResultStrings
  // in misResultCode.cxx to match.
  // Please add the prefix ( such as "file_" ) the determine your Result area

//ETX


public:
	misResultCode(void);
	~misResultCode(void);
	//	static const std::string GetStringFromResultCode(unsigned long event);
	static const std::string    GetStringFromResultCode(misResultCode::ResultIds);

	//	static unsigned long GetResultCodeFromString(const std::string event);

	static unsigned long GetLastSystemResult();
};


#endif

 
