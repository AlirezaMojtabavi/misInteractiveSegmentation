#pragma once

#include "misStrctDicomHeaderInfo.h"

struct misStrctImageData
{
	std::string PatientName;
	std::string StudyUID;
	std::string PhaseEncoding;
	int FlipAngle;
	std::string VariableFlipAngle;
	unsigned long PixelBandWidth;
	int EchoNumber;
	double ImageFrequency;
	unsigned long PercentPhaseFieldofView;
	int RepetitionTime;
	float SliceLocation;
	double SpatialResolution;
	unsigned long DistanceSourcetoDetector;
	unsigned long DistanceSourcetoPatient;
	unsigned long ExposureTime;
	int X_RayTubeCurrent;
	unsigned long Exposure;
	double KV;
	std::string PatientID;
	std::string Gender;
	std::string PatientBirthDate;
	int PatientAge;
	int PatientWeight;
	std::string StudyDescription;
	std::string StudyDate;
	std::string StudyTime;
	std::string SeriesDescription;
	std::string Modality;
	std::string AcquisitionDate;
	std::string AcquisitionTime;
	std::string ProtocolName;
	std::string Manufacturer;
	std::string ManufacturerModelName;
	std::string SoftwareVersion;
	std::string InstitutionName;
	float ImageOrientationPatient[6];
	int ImageNumber;
	float ImagePositionPatient[3];
	int SamplesperPixel;
	int Rows;
	int Columns;
	float PixelSpacing[3];
	float SpacingBetweenSlices;
	int BitsAllocated;
	int BitsStored;
	int HighBit;
	int PixelRepresentation;

	void Reset(void)
	{
		 PatientName = "";
		 StudyUID= "";
		 PhaseEncoding= "";
		 FlipAngle=-1;
		 VariableFlipAngle= "";
		 PixelBandWidth=0;
		 EchoNumber=-1;
		 ImageFrequency=-1;
		 PercentPhaseFieldofView=0;
		 RepetitionTime=-1;
		 SliceLocation=-1;
		 SpatialResolution=-1;
		 DistanceSourcetoDetector=0;
		 DistanceSourcetoPatient=0;
		 ExposureTime=0;
		 X_RayTubeCurrent=-1;
		 Exposure=0;
		 KV=-1;
		 PatientID= "";
		 Gender= "";
		 PatientBirthDate= "";
		 PatientAge=-1;
		 PatientWeight=-1;
		 StudyDescription= "";
		 StudyDate= "";
		 StudyTime= "";
		 SeriesDescription= "";
		 Modality= "";
		 AcquisitionDate= "";
		 AcquisitionTime= "";
		 ProtocolName= "";
		 Manufacturer= "";
		 ManufacturerModelName= "";
		 SoftwareVersion= "";
		 InstitutionName= "";
		 ImageNumber=-1;
		 SamplesperPixel=-1;
		 Rows=-1;
		 Columns=-1;
		 PixelSpacing[3];
		 SpacingBetweenSlices=-1;
		 BitsAllocated=-1;
		 BitsStored=-1;
		 HighBit=-1;
		 PixelRepresentation=-1;

		 ImageOrientationPatient[0] = -1;
		 ImageOrientationPatient[1] = -1;
		 ImageOrientationPatient[2] = -1;
		 ImageOrientationPatient[3] = -1;
		 ImageOrientationPatient[4] = -1;
		 ImageOrientationPatient[5] = -1;

		 ImagePositionPatient[0] = -1;
		 ImagePositionPatient[1] = -1;
		 ImagePositionPatient[2] = -1;
	};

	misStrctImageData()
	{
		this->Reset();
	}
};



