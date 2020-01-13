/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: misDIRReader.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME misDIRReader - Reads some DICOM images
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
#ifndef _misDIRReader_H
#define _misDIRReader_H


 //BTX

#include "misDataManagerTypes.h"
#include "misDcmImageReader.h"
#include "misImage.h"
#include "misImageIndexData.h"
#include "misStrctDicomIO.h"
#include "misProcessDicomData.h"

class vtkDICOMImageReaderVector;

class DICOMAppHelperModified;
class misDcmImageReader;

class misDIRReader : public vtkImageReader2
{

public:
	misDIRReader();
	virtual ~misDIRReader();
	static misDIRReader *New();
	vtkGetStringMacro(m_DirectoryName);

	virtual int CanReadFile(const char* fname);
	void	RequestStop(void);
	void	SetProgressbarValue(double val);
	void	ResetProgressbarValue();
	double	GetProgressbarValue();
	PatientsContainerViewingTypdef	GetPatientTreeWithDICOMDIR(std::string	directory);
	PatientsContainerViewingTypdef	GetPatientTreeWithoutDICOMDIR(std::string	directory);
	misStrctImageData	GetHeaderData(std::string Address1);
	std::string			GetImageAddress(misImageIndexData add);
	std::string			FindSerieAddress(misImageIndexData add);	
	SeriAddress			GetSpecificSeriProperty(misImageIndexData add);
	imageListTypdef		FindSerie(SeriAddress add);
	misUID	FindSerieUID(misImageIndexData add);
protected:
	DICOMParser* Parser;
	DICOMAppHelperModified* AppHelper;
	misProcessDicomData* ProcessDicomData;

	char* m_DirectoryName;
	char* m_PatientName;
	char* m_StudyUID;
	char* m_StudyID;
	char* m_TransferSyntaxUID;

private:
	PatientsContainerViewingTypdef	GetDataFromDICOMDIR(gdcm::DicomDir* DicomDirData);
	void							ReadPatientsData(gdcm::DicomDir *DicomDirData);
	SeriesType			GetSeriesData(gdcm::DicomDirStudy *Study);
	StudyType			GetStudiesData(gdcm::DicomDirPatient *Patient);
	imageListTypdef					GetImagesData(gdcm::DicomDirSerie *Serie);
	vtkDICOMImageReaderVector*		ExtractDCMFromDIR(imageListTypdef listOfDIR );
	SerieUid2Data					GetDatafromDCM(vtkDICOMImageReaderVector* DICOMFileNames);
	static void						ProgressMethod(void* pInstance);

	std::map<std::string,misStrctImageData> ImageHeaderData;
	Uid2Description m_Uid2Description;

	std::map<std::string,std::string> ImageAddresstoName;
	PatientsType	m_Patients;
	int		m_SortingMethod;
	bool	m_CancelRequested;
	//IMPORTANTNOTE: To access this value, it's set and get method must used.
	double	m_ProgressbarValue;
	
};
#endif
