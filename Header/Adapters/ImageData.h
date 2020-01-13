#pragma once

#include "DateTime.h"

namespace parcast
{

	typedef std::shared_ptr<std::vector<std::uint8_t>> ByteArrayPtr;

	struct ImageData
	{
		bool IsDirectionConfirmed = false;
		long long int ScalarType = 0;
		long long int FileDimensionality = 0;
		long long int NumberOfComponent = 0;
		long long int ImageType;
		double ThresholdForSkinViewing = 0.0;
		double ThresholdForBoneViewing = 0.0;
		std::string	ImageUid;
		std::string	ImagePrimaryUid;
		std::string	SolutionUid;
		std::string	ParentImageUid;
		std::string	ImageName;
		ByteArrayPtr Extent;
		ByteArrayPtr Spacing;
		ByteArrayPtr Roi;
	
		struct
		{
			ByteArrayPtr PixelSpacing;
			long long int PixelRepresentation;
			long long int SamplesPerPixel;
			long long int NumberOfImages;
			long long int BitsAllocated;
			long long int BitsStored;
			long long int Columns;
			long long int HighBit;
			long long int Rows;
		} ImageProperties;

		struct
		{
			long long int ViewingNameType;
			long long int ColorMapType;
			double DefaultWindowCenter;
			double DefaultWindowWidth;
			double WindowCenter;
			double WindowWidth;
		} ViewingProperties;

		struct
		{
			std::string StudyUid;
			std::string	StudyDescription;
			std::string StudyTime;
			std::string	StudyDate;
		} StudyProperties;

		struct
		{
			std::string	DistanceSourceToDetector;
			std::string	DistanceSourceToPatient;
			std::string	PercentPhaseFieldOfView;
			std::string	VariableFlipAngle;
			std::string	PixelBandWidth;
			std::string	PhaseEncoding;
			std::string	ProtocolName;
			std::string	ExposureTime;
			std::string	Exposure;
			long long int XRayTubeCurrent;
			long long int RepetitionTime;
			long long int ImageModality;
			long long int EchoNumber;
			long long int FlipAngle;
			double SpatialResolution;
			double ImageFrequency;
			double KV;
		} ImagingProperties;

		struct
		{
			std::string SerieUid;
			std::string	SeriesDescription;
			std::string	AcquisitionDate;
			std::string	AcquisitionTime;
		} SeriesProperties;

		struct
		{
			std::string	ManufacturerModelName;
			std::string	InstitutionName;
			std::string	SoftwareVersion;
			std::string	Manufacturer;
		} HardwareProperties;
	};

}
