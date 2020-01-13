/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: misDICOMImageReader.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME misDICOMImageReader - Reads some DICOM images
// .SECTION Description
// DICOM (stands for Digital Imaging in COmmunications and Medicine)
// is a medical image file format widely used to exchange data, provided
// by various modalities.
// .SECTION Warnings
// This reader might eventually handle ACR-NEMA file (predecessor of the DICOM
// format for medical images).
// This reader does not handle encapsulated format, only plain raw file are
// handled. This reader also does not handle multi-frames DICOM datasets.
// .SECTION See Also
// vtkBMPReader vtkPNMReader vtkTIFFReader

#pragma once 

#include "misDataManagerTypes.h"
#include "misImage.h"
#include "misSerieCheckValidation.h"
#include "misImageDataProperties.h"

class vtkDICOMImageReaderVector;

class misDicomException:public std::exception
{
public:
	misDicomException(const std::string& what = "") ;
	virtual ~misDicomException() throw() {}

	virtual const char* what() const throw();
protected:
	std::string what_;
};

class misDcmImageReader : public vtkImageReader2
{
//
 public:
	 std::unique_ptr<misImage>    GetImage(void);
	static misDcmImageReader* New();

  // Description:
  // Prints the ivars.
  void PrintSelf(std::ostream& os, vtkIndent indent);

  // Description:
  // Set the filename for the file to read. If this method is used,
  // the reader will only read a single file.
  void SetFileName(const char* fn)
  {
    if (this->DirectoryName)
      {
      delete [] this->DirectoryName;
      }
    if (this->FileName)
      {
      delete [] this->FileName;
      }
    this->DirectoryName = NULL;
    this->FileName = NULL;
    this->vtkImageReader2::SetFileName(fn);
  }
  void SetDicomFileNames(std::vector<std::string>& Input);

  // Description:
  // Returns the directory name.
  vtkGetStringMacro(DirectoryName);

  // Description:
  // Returns the pixel spacing.
  double* GetPixelSpacing();

  // Description:
  // Returns the image width.
  int GetWidth();

  // Description:
  // Returns the image height.
  int GetHeight();

  // Description:
  // Get the (DICOM) x,y,z coordinates of the first pixel in the
  // image (upper left hand corner) of the last image processed by the
  // DICOMParser
  float* GetImagePositionPatient();

  // Description:
  // Get the (DICOM) directions cosines. It consist of the components
  // of the first two vectors. The third vector needs to be computed
  // to form an orthonormal basis.
  float* GetImageOrientationPatient();

  // Description:
  // Get the number of bits allocated for each pixel in the file.
  int GetBitsAllocated();

  // Description:
  // Get the pixel representation of the last image processed by the
  // DICOMParser. A zero is a unsigned quantity.  A one indicates a
  // signed quantity
  int GetPixelRepresentation();

  // Description:
  // Get the number of components of the image data for the last
  // image processed.
  int GetNumberOfComponents();

  // Description:
  // Get the transfer syntax UID for the last image processed.
  const char* GetTransferSyntaxUID();

  // Description:
  // Get the rescale slope for the pixel data.
  float GetRescaleSlope();

  // Description:
  // Get the rescale offset for the pixel data.
  float GetRescaleOffset();

  // Description:
  // Get the patient name for the last image processed.
  const char* GetPatientName();

  // Description:
  // Get the study uid for the last image processed.
  const char* GetStudyUID();

  // Description:
  // Get the Study ID for the last image processed.
  const char* GetStudyID();

  // Description:
  // Get the gantry angle for the last image processed.
  float GetGantryAngle();

  //
  // Can I read the file?
  //
  virtual int CanReadFile(const char* fname);

  //
  // What file extensions are supported?
  //
  virtual const char* GetFileExtensions()
  {
    return ".dcm";
  }

  // Description:
  // Return a descriptive name for the file format that might be useful in a GUI.
  virtual const char* GetDescriptiveName()
  {
    return "DICOM";
  }
  misImageDataProperties GetImageDataProperties();
  virtual ~misDcmImageReader();
  misDcmImageReader();

protected:
  //
  // Setup the volume size
  //
  void SetupOutputInformation(int num_slices);

  virtual void ExecuteInformation();
  void ExecuteBasedOnDicomFileSize();
  void ExecuteBasedOnDirecteryName();
  void ExecuteBasedOnFileName();

  virtual void ExecuteDataWithInformation(vtkDataObject *out, vtkInformation *outInfo); 
  //
  // Instance of the parser used to parse the file.
  //
  DICOMParser* Parser;
  //
  // Instance of the callbacks that get the data from the file.
  //
  DICOMAppHelperModified* AppHelper;
  //
  // vtkDICOMImageReaderVector wants to be a PIMPL and it will be, but not quite yet.
  //
  std::vector<std::string> DICOMFileNames;
  char* DirectoryName;
  std::vector<std::string> SelectedDICOMFileNames;
  char* PatientName;
  char* StudyUID;
  char* StudyID;
  char* TransferSyntaxUID;
  int SortingType;

public:
	// DICOMFileNames accessors methods for subclasses:
	int			GetNumberOfDICOMFileNames();
	const char*	GetDICOMFileName(int index);

	misDicomDataViewingProperties GetViewingProperties(imageListTypdef DICOMSerieFileNames);
	std::unique_ptr<misImage> Get3DImageData(imageListTypdef DICOMSerieFileNames);

	vtkImageData* Get2DImageData(std::string Address1);

private:
	std::shared_ptr<misImage>	GetSpecificImageData(imageListTypdef DICOMSerieFileNames);

	void ReadAllImageProperties(void);

	misImageProperties  ReadImageProperties(void);
	misImageingProperties ReadImagingProperties(void);
	misHardwareProperties ReadHardwareProperties(void);
	misPatientProperties ReadPatientProperties(void);
	misSerieProperties ReadSerieProperties(void);
	misStudyProperties ReadStudyProperties(void);

  misDcmImageReader(const misDcmImageReader&);  // Not implemented.
  void operator=(const misDcmImageReader&);  // Not implemented.
  misImageDataProperties ImageDataProperties;
};

