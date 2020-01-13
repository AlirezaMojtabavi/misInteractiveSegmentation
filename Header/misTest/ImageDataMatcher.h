#pragma once
#pragma once

#include "DateTime.h"
#include <ImageData.h>
#include "DateTimeMatcher.h"

namespace parcast
{

	class ImageDataMatcher
	{
	public:
		ImageDataMatcher(const ImageData & d) : m_ImageData(d)
		{

		}

		bool operator()(const ImageData & other) const
		{
			return IsEqual(m_ImageData, other);
		}

		static bool IsEqual(const ImageData & a, const ImageData & b)
		{
			bool isEqual =
				a.ImageUid == b.ImageUid &&
				a.ImagePrimaryUid == b.ImagePrimaryUid &&
				a.SolutionUid == b.SolutionUid &&
				a.ImageName == b.ImageName &&
				a.IsDirectionConfirmed == b.IsDirectionConfirmed &&
				a.ScalarType == b.ScalarType &&
				a.FileDimensionality == b.FileDimensionality &&
				a.NumberOfComponent == b.NumberOfComponent &&
				a.ImageType == b.ImageType &&
				a.ThresholdForSkinViewing == b.ThresholdForSkinViewing &&
				a.ThresholdForBoneViewing == b.ThresholdForBoneViewing &&
				*a.Roi == *a.Roi &&
				*a.Extent == *b.Extent &&
				*a.Spacing == *b.Spacing &&

				a.ViewingProperties.ViewingNameType == b.ViewingProperties.ViewingNameType &&
				a.ViewingProperties.ColorMapType == b.ViewingProperties.ColorMapType &&
				a.ViewingProperties.DefaultWindowCenter == b.ViewingProperties.DefaultWindowCenter &&
				a.ViewingProperties.DefaultWindowWidth == b.ViewingProperties.DefaultWindowWidth &&
				a.ViewingProperties.WindowCenter == b.ViewingProperties.WindowCenter &&
				a.ViewingProperties.WindowWidth == b.ViewingProperties.WindowWidth &&

				*a.ImageProperties.PixelSpacing == *b.ImageProperties.PixelSpacing &&
				a.ImageProperties.BitsAllocated == b.ImageProperties.BitsAllocated &&
				a.ImageProperties.BitsStored == b.ImageProperties.BitsStored &&
				a.ImageProperties.Columns == b.ImageProperties.Columns &&
				a.ImageProperties.Rows == b.ImageProperties.Rows &&
				a.ImageProperties.HighBit == b.ImageProperties.HighBit &&
				a.ImageProperties.NumberOfImages == b.ImageProperties.NumberOfImages &&
				a.ImageProperties.SamplesPerPixel == b.ImageProperties.SamplesPerPixel &&
				a.ImageProperties.PixelRepresentation == b.ImageProperties.PixelRepresentation &&

				a.StudyProperties.StudyUid == b.StudyProperties.StudyUid &&
				a.StudyProperties.StudyDate == b.StudyProperties.StudyDate &&
				a.StudyProperties.StudyDescription == b.StudyProperties.StudyDescription &&
				a.StudyProperties.StudyTime == b.StudyProperties.StudyTime &&

				a.ImagingProperties.DistanceSourceToDetector == b.ImagingProperties.DistanceSourceToDetector &&
				a.ImagingProperties.DistanceSourceToPatient == b.ImagingProperties.DistanceSourceToPatient &&
				a.ImagingProperties.PercentPhaseFieldOfView == b.ImagingProperties.PercentPhaseFieldOfView &&
				a.ImagingProperties.VariableFlipAngle == b.ImagingProperties.VariableFlipAngle &&
				a.ImagingProperties.PixelBandWidth == b.ImagingProperties.PixelBandWidth &&
				a.ImagingProperties.PhaseEncoding == b.ImagingProperties.PhaseEncoding &&
				a.ImagingProperties.ProtocolName == b.ImagingProperties.ProtocolName &&
				a.ImagingProperties.ExposureTime == b.ImagingProperties.ExposureTime &&
				a.ImagingProperties.Exposure == b.ImagingProperties.Exposure &&
				a.ImagingProperties.XRayTubeCurrent == b.ImagingProperties.XRayTubeCurrent &&
				a.ImagingProperties.RepetitionTime == b.ImagingProperties.RepetitionTime &&
				a.ImagingProperties.ImageModality == b.ImagingProperties.ImageModality &&
				a.ImagingProperties.EchoNumber == b.ImagingProperties.EchoNumber &&
				a.ImagingProperties.FlipAngle == b.ImagingProperties.FlipAngle &&
				a.ImagingProperties.SpatialResolution == b.ImagingProperties.SpatialResolution &&
				a.ImagingProperties.ImageFrequency == b.ImagingProperties.ImageFrequency &&
				a.ImagingProperties.KV == b.ImagingProperties.KV &&

				a.SeriesProperties.SerieUid == b.SeriesProperties.SerieUid &&
				a.SeriesProperties.SeriesDescription == b.SeriesProperties.SeriesDescription &&
				a.SeriesProperties.AcquisitionDate == b.SeriesProperties.AcquisitionDate &&
				a.SeriesProperties.AcquisitionTime == b.SeriesProperties.AcquisitionTime &&

				a.HardwareProperties.ManufacturerModelName == b.HardwareProperties.ManufacturerModelName &&
				a.HardwareProperties.InstitutionName == b.HardwareProperties.InstitutionName &&
				a.HardwareProperties.SoftwareVersion == b.HardwareProperties.SoftwareVersion &&
				a.HardwareProperties.Manufacturer == b.HardwareProperties.Manufacturer;
			return isEqual;
		}

	private:
		const ImageData& m_ImageData;

	};

}
