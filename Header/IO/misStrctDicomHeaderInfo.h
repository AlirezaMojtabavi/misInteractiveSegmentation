#pragma once

#include "misEnums.h"
#include "misImageModalityEnum.h"
#include "misImageProperties.h"
#include "misStrctPatientData.h"
#include "misWindowLevelStr.h"

struct misCTImageingProperties
{
	std::string DistanceSourcetoDetector;
	std::string DistanceSourcetoPatient;
	std::string ExposureTime;
	int			X_RayTubeCurrent;
	std::string Exposure;
	double	    KV;

	void Reset()
	{
		DistanceSourcetoDetector = "";
		DistanceSourcetoPatient  = "";
		ExposureTime             = "";
		X_RayTubeCurrent = -1;
		Exposure                 = "";
		KV= -1;
	};

	misCTImageingProperties()
	{
		this->Reset();
	}
};
struct misMRImageingProperties
{
	std::string PhaseEncoding;
	int         FlipAngle;
	std::string VariableFlipAngle;
	std::string PixelBandWidth;
	int			EchoNumber;
	double		ImageFrequency;
	std::string PercentPhaseFieldofView;
	int			RepetitionTime;
	double		SpatialResolution;
	void Reset()
	{
		PhaseEncoding = "";
		FlipAngle     = -1;
		VariableFlipAngle  = "";
		PixelBandWidth     = "";
		EchoNumber         =-1;
		ImageFrequency     =-1;
		PercentPhaseFieldofView ="";
		RepetitionTime    = -1;
		SpatialResolution = -1;
	};

	misMRImageingProperties()
	{
		this->Reset();
	};

};
struct misImageingProperties
{
public :

	misImageDataModality    ImageModality; 
	std::string             ProtocolName;
	misCTImageingProperties CTDATA;
	misMRImageingProperties MRDATA;

	void Reset()
	{
		ImageModality = NoData; 
		ProtocolName = "";
		CTDATA.Reset();
		MRDATA.Reset();
	};
	misImageingProperties()
	{
		this->Reset();
	}
	static std::string ImageDataModalityEnumToString(misImageDataModality modality)
	{
		std::string sModality;

		switch (modality)
		{
		case CT :
			sModality = "CT";
			break;

		case MRI :
			sModality = "MRI";
			break;
		case fMRI :
			sModality = "fMRI";
			break;
		case XRay :
			sModality = "XRay";
			break;

		case DXRay :
			sModality = "DXRay";
			break;

		case PET :
			sModality = "PET";
			break;

		case SPECT :
			sModality = "SPECT";
			break;

		case Angio :
			sModality = "Angio";
			break;

		case DAngio :
			sModality = "DAngio";
			break;

		case US :
			sModality = "CT";
			break;

		case NM :
			sModality = "NM";
			break;

		case NoData :
			sModality = "NoData";
			break;

		default:
			sModality = "Empty";

		}

		return sModality;
	}

	static misImageDataModality CharPointerToImageDataModalityEnum(const char* imageDataModality)
	{
		if ( std::strcmp(imageDataModality,"CT") == 0  )
			return CT;
		if ( std::strcmp(imageDataModality, "MRI") == 0 )
			return MRI;
		if ( std::strcmp(imageDataModality, "fMRI") == 0 )
			return fMRI;
		if ( std::strcmp(imageDataModality, "XRay") == 0 )
			return XRay;
		if ( std::strcmp(imageDataModality, "DXRay") == 0 )
			return DXRay;
		if ( std::strcmp(imageDataModality, "PET") == 0 )
			return PET;
		if ( std::strcmp(imageDataModality, "SPECT") == 0 )
			return SPECT;
		if ( std::strcmp(imageDataModality, "Angio") == 0 )
			return Angio;
		if ( std::strcmp(imageDataModality, "DAngio") == 0 )
			return DAngio;
		if ( std::strcmp(imageDataModality, "US") == 0 )
			return US;
		if ( std::strcmp(imageDataModality, "NM") == 0 )
			return NM;
		else
			return NoData;
	}
};
struct misHardwareProperties
{
	std::string Manufacturer;
	std::string ManufacturerModelName;
	std::string SoftwareVersion;
	std::string InstitutionName;

	void Reset(void)
	{
		Manufacturer          = "";
		ManufacturerModelName = "";
		SoftwareVersion       = "";
		InstitutionName       = "";
	};
	misHardwareProperties()
	{
		Reset();
	};

};


struct misSerieProperties
{
	std::string SeriesDescription;
	std::string AcquisitionDate;
	std::string AcquisitionTime;
	std::string SerieUID;

	void Reset(void)
	{
		SeriesDescription ="";
		AcquisitionDate   ="";
		AcquisitionTime   ="";
		SerieUID          ="";
	};

	misSerieProperties()
	{
		this->Reset();
	};
};
struct misStudyProperties
{
	std::string StudyDescription;
	std::string StudyDate;
	std::string StudyTime;
	std::string StudyUID;

	void Reset(void)
	{
		StudyDescription ="";
		StudyDate        ="";
		StudyTime        ="";
		StudyUID         ="";
	};

	misStudyProperties()
	{
		this->Reset();
	};
}; 

