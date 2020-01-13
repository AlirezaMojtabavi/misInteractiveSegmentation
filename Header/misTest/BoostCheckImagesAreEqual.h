#pragma once

#include "IImage.h"
#include "misGuiStructures.h"
#include "misImageViewingProperties.h"
#include "misStrctDicomHeaderInfo.h"
#include "misImageIOProperties.h"
#include "misImageDataProperties.h"

namespace parcast
{

	class BoostCheckImagesAreEqual
	{
	public:
		static void Check(std::shared_ptr<IImage> a, std::shared_ptr<IImage> b)
		{
			auto dimsA = a->GetRawImageData()->GetDimensions(), dimsB = b->GetRawImageData()->GetDimensions();
			auto sizeA = a->GetRawImageData()->GetScalarSize(), sizeB = b->GetRawImageData()->GetScalarSize();
			auto numScalarsA = a->GetRawImageData()->GetNumberOfScalarComponents();
			auto numScalarsB = b->GetRawImageData()->GetNumberOfScalarComponents();
			BOOST_REQUIRE_EQUAL_COLLECTIONS(dimsA, dimsA + 3, dimsB, dimsB + 3);
			BOOST_REQUIRE_EQUAL(sizeA, sizeB);
			BOOST_REQUIRE_EQUAL(numScalarsA, numScalarsB);

			int sizeOfImages = dimsA[0] * dimsA[1] * dimsA[2] * sizeA * numScalarsA;
			bool rawImageEqual = true;
			auto rawDataPtrA = reinterpret_cast<char*>(a->GetScalarPointer());
			auto rawDataPtrB = reinterpret_cast<char*>(b->GetScalarPointer());
			for (int i = 0; i < sizeOfImages; i += 100)
			{
				rawImageEqual = (rawDataPtrA[i] == rawDataPtrB[i]);
				if (!rawImageEqual)
					break;
			}
			BOOST_CHECK(rawImageEqual);

			BoostCheckMisDicomDataViewingProperties(a->GetSimplifiedProperties(), b->GetSimplifiedProperties());
			auto spacingA = a->GetSpacing(), spacingB = b->GetSpacing();
			BOOST_CHECK_EQUAL_COLLECTIONS(spacingA, spacingA + 3, spacingB, spacingB + 3);
			BOOST_CHECK_EQUAL(a->GetName(), b->GetName());
			BOOST_CHECK_EQUAL(a->GetObjectType(), b->GetObjectType());
			BOOST_CHECK_EQUAL(a->GetScalarType(), b->GetScalarType());
			BOOST_CHECK_EQUAL(a->GetViewingNameCompletenessStatus(), b->GetViewingNameCompletenessStatus());
			BOOST_CHECK_EQUAL(a->GetConfirmedDirection(), b->GetConfirmedDirection());
			BOOST_CHECK_EQUAL(a->GetCurrentBoneThreshold(), b->GetCurrentBoneThreshold());
			BOOST_CHECK_EQUAL(a->GetCurrentSkinThreshold(), b->GetCurrentSkinThreshold());
			BOOST_CHECK_EQUAL(a->GetCurrentTeethThreshold(), b->GetCurrentTeethThreshold());
			BOOST_CHECK_EQUAL(a->GetDeafaultSkinThreshold(), b->GetDeafaultSkinThreshold());
			BOOST_CHECK_EQUAL(a->GetImageModality(), b->GetImageModality());
			BOOST_CHECK_EQUAL(a->GetParentImageUID(), b->GetParentImageUID());
			BOOST_CHECK_EQUAL(a->GetDuplicatedRangeActivation(), b->GetDuplicatedRangeActivation());

			BoostCheckMisImageRoi(a->GetROI(), b->GetROI());
			BoostCheckMisImageRoi(a->GetWorldDiemension(), b->GetWorldDiemension());

			auto scalarRangeNeededA = a->GetScalerRangeNeeded(), scalarRangeNeededB = b->GetScalerRangeNeeded();
			BOOST_CHECK_EQUAL_COLLECTIONS(scalarRangeNeededA.begin(), scalarRangeNeededA.end(),
				scalarRangeNeededB.begin(), scalarRangeNeededB.end());
			BOOST_CHECK_EQUAL(a->GetPrimeryUID(), b->GetPrimeryUID());

			BoostCheckEqualMisImageIOProperties(a->GetImageIOProperties(), b->GetImageIOProperties());
			BoostCheckEqualMisImageDataProperties(*a->GetImageDataProperties(), *b->GetImageDataProperties());
			BoostCheckEqualMisImageViewingItemsStruct(a->GetViewingStrct(), b->GetViewingStrct());
			BOOST_CHECK_EQUAL_COLLECTIONS(a->GetDimensions(), a->GetDimensions() + 3, b->GetDimensions(), b->GetDimensions() + 3);

			auto imageCenterA = a->GetImageCenter();
			auto imageCenterB = b->GetImageCenter();
			BOOST_CHECK_EQUAL_COLLECTIONS(imageCenterA.Elements(), imageCenterA.Elements() + 3, imageCenterB.Elements(),
 imageCenterB.Elements() + 3);
		}

	private:
		static void BoostCheckMisDicomDataViewingProperties(const misDicomDataViewingProperties& a, const misDicomDataViewingProperties& b)
		{
			BoostCheckMisViewingPatientProperties(a.patientProperties, b.patientProperties);
			BoostCheckMisViewingImageProperties(a.imageProperties, b.imageProperties);
			BoostCheckMisStudySerieViewingProperties(a.studySerieProperties, b.studySerieProperties);
		}

		static void BoostCheckEqualMisImageViewingItemsStruct(const misImageViewingItemsStruct& a, const misImageViewingItemsStruct& b)
		{
			BOOST_CHECK_EQUAL(a.viewingName, b.viewingName);
			BOOST_CHECK_EQUAL(a.name, b.name);
			BOOST_CHECK_EQUAL(a.description, b.description);
			BOOST_CHECK_EQUAL(a.numberofImages, b.numberofImages);
			BOOST_CHECK_EQUAL(a.modality, b.modality);
			BOOST_CHECK_EQUAL(a.Dimention, b.Dimention);
			BOOST_CHECK_EQUAL(a.Spacing, b.Spacing);
			BOOST_CHECK_EQUAL(a.objectUID, b.objectUID);
			BOOST_CHECK_EQUAL(a.packageUID, b.packageUID);
			BOOST_CHECK_EQUAL(a.directionSataus, b.directionSataus);
			BOOST_CHECK_EQUAL(a.correlationSatus, b.correlationSatus);
			BOOST_CHECK_EQUAL(a.visibilitySatus, b.visibilitySatus);
			BOOST_CHECK_EQUAL(a.makeCompleteName, b.makeCompleteName);
		}

		static void BoostCheckMisImageRoi(const misROI& a, const misROI& b)
		{
			double d1[6], d2[6];
			a.getData(d1);
			b.getData(d2);
			BOOST_CHECK_EQUAL_COLLECTIONS(d1, d1 + 6, d2, d2 + 6);
			BOOST_CHECK_EQUAL(a.IsInitilized(), b.IsInitilized());
			BOOST_CHECK_EQUAL(a.IsPermanent(), b.IsPermanent());
			BOOST_CHECK_EQUAL(a.GetVolume(), b.GetVolume());
			BOOST_CHECK_EQUAL(a.IsValid(), b.IsValid());
			BOOST_CHECK_EQUAL(a.GetWidth(), b.GetWidth());
			BOOST_CHECK_EQUAL(a.GetHeight(), b.GetHeight());
			BOOST_CHECK_EQUAL(a.GetDepth(), b.GetDepth());
			BOOST_CHECK_EQUAL(a.GetMinPoint(), b.GetMinPoint());
			BOOST_CHECK_EQUAL(a.GetMaxPoint(), b.GetMaxPoint());
		}

		static void BoostCheckMisViewingPatientProperties(const misViewingPatientProperties& a, const misViewingPatientProperties& b)
		{
			BOOST_CHECK_EQUAL(a.FamilyName, b.FamilyName);
			BOOST_CHECK_EQUAL(a.Gender, b.Gender);
			BOOST_CHECK_EQUAL(a.BirthData, b.BirthData);
			BOOST_CHECK_EQUAL(a.Weight, b.Weight);
			BOOST_CHECK_EQUAL(a.Age, b.Age);
		}

		static void BoostCheckMisViewingImageProperties(const misViewingImageProperties& a, const misViewingImageProperties& b)
		{
			BOOST_CHECK_EQUAL(a.ImageModality, b.ImageModality);
			BOOST_CHECK_EQUAL(a.ProtocolName, b.ProtocolName);
			BOOST_CHECK_EQUAL(a.NumberofImages, b.NumberofImages);
			BOOST_CHECK_EQUAL(a.ZResolution, b.ZResolution);
			BOOST_CHECK_EQUAL(a.Rows, b.Rows);
			BOOST_CHECK_EQUAL(a.Columns, b.Columns);
		}

		static void BoostCheckMisStudySerieViewingProperties(const misStudySerieViewingProperties& a, const misStudySerieViewingProperties& b)
		{
			BOOST_CHECK_EQUAL(a.SeriesDescription, b.SeriesDescription);
			BOOST_CHECK_EQUAL(a.SerieAcquisitionDate, b.SerieAcquisitionDate);
			BOOST_CHECK_EQUAL(a.SerieAcquisitionTime, b.SerieAcquisitionTime);
			BOOST_CHECK_EQUAL(a.StudyDescription, b.StudyDescription);
			BOOST_CHECK_EQUAL(a.StudyDate, b.StudyDate);
		}

		static void BoostCheckEqualMisImageIOProperties(const misImageIOProperties& a, const misImageIOProperties& b)
		{
			BOOST_CHECK_EQUAL(a.NumberOfComponent, b.NumberOfComponent);
			BOOST_CHECK_EQUAL_COLLECTIONS(a.extent, a.extent + 6, b.extent, b.extent + 6);
			BOOST_CHECK_EQUAL_COLLECTIONS(a.spacing, a.spacing + 3, b.spacing, b.spacing + 3);
			BOOST_CHECK_EQUAL(a.scalerType, b.scalerType);
			BOOST_CHECK_EQUAL(a.fileDimensionality, b.fileDimensionality);
			BOOST_CHECK_EQUAL_COLLECTIONS(a.FOVExtent, a.FOVExtent + 6, b.FOVExtent, b.FOVExtent + 6);
			BoostCheckMisImageRoi(a.GetRoi(), b.GetRoi());
		}

		static void BoostCheckEqualMisImageDataProperties(const misImageDataProperties& a, const misImageDataProperties& b)
		{
			BOOST_CHECK_EQUAL(a.GetCurrentThresholdForSkinViewing(), b.GetCurrentThresholdForSkinViewing());
			BOOST_CHECK_EQUAL(a.GetDefaultThresholdForSkinViewing(), b.GetDefaultThresholdForSkinViewing());
			BOOST_CHECK_EQUAL(a.GetViewingNameType(), b.GetViewingNameType());
			BoostCheckMisWindowLevelStr(a.GetWindowlevel(), b.GetWindowlevel());
			BOOST_CHECK_EQUAL(a.GetCurrentThresholdForBoneViewing(), b.GetCurrentThresholdForBoneViewing());
			BOOST_CHECK_EQUAL(a.GetCurrentThresholdForTeethViewing(), b.GetCurrentThresholdForTeethViewing());
			BOOST_CHECK_EQUAL(a.GetColorMapType(), b.GetColorMapType());
			BoostCheckEqualMisImageViewingProperties(a.GetViewingProperties(), b.GetViewingProperties());
			BoostCheckEqualMisImageingProperties(a.imagingProprties, b.imagingProprties);
			BoostCheckEqualMisPatientProperties(a.patientProperties, b.patientProperties);
			BoostCheckEqualMisHardwareProperties(a.hardwareProperties, b.hardwareProperties);
			BoostCheckMisSerieProperties(a.serieProperties, b.serieProperties);
			BoostCheckEqualMisStudyProperties(a.studyProperties, b.studyProperties);
			BoostCheckEqualMisImageProperties(a.imageProperties, b.imageProperties);
		}

		static void BoostCheckMisWindowLevelStr(const misWindowLevelStr& a, const misWindowLevelStr& b)
		{
			BOOST_CHECK_EQUAL(a.GetWindowCenter(), b.GetWindowCenter());
			BOOST_CHECK_EQUAL(a.GetWindowWidth(), b.GetWindowWidth());
		}

		static void BoostCheckEqualMisImageViewingProperties(const misImageViewingProperties& a, const misImageViewingProperties& b)
		{
			BOOST_CHECK_EQUAL(a.GetCurrentThresholdForSkinViewing(), b.GetCurrentThresholdForSkinViewing());
			BOOST_CHECK_EQUAL(a.GetCurrentThresholdForBoneViewing(), b.GetCurrentThresholdForBoneViewing());
			BOOST_CHECK_EQUAL(a.GetCurrentThresholdForTeethViewing(), b.GetCurrentThresholdForTeethViewing());
			BOOST_CHECK_EQUAL(a.GetCurrentThresholdForSkinFilledViewing(), b.GetCurrentThresholdForSkinFilledViewing());
			BoostCheckMisWindowLevelStr(a.GetLevelWindow(), b.GetLevelWindow());
			BOOST_CHECK_EQUAL(a.GetViewingNameType(), b.GetViewingNameType());
			BOOST_CHECK_EQUAL(a.GetColorMapType(), b.GetColorMapType());
			BoostCheckMisWindowLevelStr(a.GetInitialLevelWindow(), b.GetInitialLevelWindow());
		}

		static void BoostCheckEqualMisImageingProperties(const misImageingProperties& a, const misImageingProperties& b)
		{
			BOOST_CHECK_EQUAL(a.ImageModality, b.ImageModality);
			BOOST_CHECK_EQUAL(a.ProtocolName, b.ProtocolName);
			BoostCheckEqualMisCTImageingProperties(a.CTDATA, b.CTDATA);
			BoostCheckEqualMisMRImageingProperties(a.MRDATA, b.MRDATA);
		}

		static void BoostCheckEqualMisCTImageingProperties(const misCTImageingProperties& a, const misCTImageingProperties& b)
		{
			BOOST_CHECK_EQUAL(a.DistanceSourcetoDetector, b.DistanceSourcetoDetector);
			//BOOST_CHECK_EQUAL(a.DistanceSourcetoPatient, b.DistanceSourcetoPatient);
			BOOST_CHECK_EQUAL(a.ExposureTime, b.ExposureTime);
			BOOST_CHECK_EQUAL(a.X_RayTubeCurrent, b.X_RayTubeCurrent);
			BOOST_CHECK_EQUAL(a.Exposure, b.Exposure);
			BOOST_CHECK_EQUAL(a.KV, b.KV);
			BOOST_CHECK_EQUAL(a.KV, b.KV);
		}

		static void BoostCheckEqualMisMRImageingProperties(const misMRImageingProperties& a, const misMRImageingProperties& b)
		{
			BOOST_CHECK_EQUAL(a.PhaseEncoding, b.PhaseEncoding);
			BOOST_CHECK_EQUAL(a.FlipAngle, b.FlipAngle);
			BOOST_CHECK_EQUAL(a.VariableFlipAngle, b.VariableFlipAngle);
			BOOST_CHECK_EQUAL(a.PixelBandWidth, b.PixelBandWidth);
			BOOST_CHECK_EQUAL(a.EchoNumber, b.EchoNumber);
			BOOST_CHECK_EQUAL(a.ImageFrequency, b.ImageFrequency);
			BOOST_CHECK_EQUAL(a.PercentPhaseFieldofView, b.PercentPhaseFieldofView);
			BOOST_CHECK_EQUAL(a.RepetitionTime, b.RepetitionTime);
			BOOST_CHECK_EQUAL(a.SpatialResolution, b.SpatialResolution);
		}

		static void BoostCheckEqualMisPatientProperties(const misPatientProperties& a, const misPatientProperties& b)
		{
			BOOST_CHECK_EQUAL(a.GetAge(), b.GetAge());
			BOOST_CHECK_EQUAL(a.GetBirthDate(), b.GetBirthDate());
			BOOST_CHECK_EQUAL(a.NationalCode, b.NationalCode);
			BOOST_CHECK_EQUAL(a.FirstName, b.FirstName);
			BOOST_CHECK_EQUAL(a.Gender, b.Gender);
			BOOST_CHECK_EQUAL(a.Weight, b.Weight);
			BOOST_CHECK_EQUAL(a.Position, b.Position);
			BOOST_CHECK_EQUAL(a.ReadyForSurgery, b.ReadyForSurgery);
		}

		static void BoostCheckEqualMisHardwareProperties(const misHardwareProperties& a, const misHardwareProperties& b)
		{
			BOOST_CHECK_EQUAL(a.Manufacturer, b.Manufacturer);
			BOOST_CHECK_EQUAL(a.ManufacturerModelName, b.ManufacturerModelName);
			BOOST_CHECK_EQUAL(a.SoftwareVersion, b.SoftwareVersion);
			BOOST_CHECK_EQUAL(a.InstitutionName, b.InstitutionName);
		}

		static void BoostCheckMisSerieProperties(const misSerieProperties& a, const misSerieProperties& b)
		{
			BOOST_CHECK_EQUAL(a.SeriesDescription, b.SeriesDescription);
			BOOST_CHECK_EQUAL(a.AcquisitionDate, b.AcquisitionDate);
			BOOST_CHECK_EQUAL(a.AcquisitionTime, b.AcquisitionTime);
			//BOOST_CHECK_EQUAL(a.SerieUID, b.SerieUID);
		}

		static void BoostCheckEqualMisStudyProperties(const misStudyProperties& a, const misStudyProperties& b)
		{
			BOOST_CHECK_EQUAL(a.StudyDescription, b.StudyDescription);
			BOOST_CHECK_EQUAL(a.StudyDate, b.StudyDate);
			BOOST_CHECK_EQUAL(a.StudyTime, b.StudyTime);
			//BOOST_CHECK_EQUAL(a.StudyUID, b.StudyUID);
		}

		static void BoostCheckEqualMisImageProperties(const misImageProperties& a, const misImageProperties& b)
		{
			BOOST_CHECK_EQUAL(a.SamplesperPixel, b.SamplesperPixel);
			BOOST_CHECK_EQUAL(a.Rows, b.Rows);
			BOOST_CHECK_EQUAL(a.Columns, b.Columns);
			BOOST_CHECK_EQUAL(a.BitsAllocated, b.BitsAllocated);
			BOOST_CHECK_EQUAL(a.BitsStored, b.BitsStored);
			BOOST_CHECK_EQUAL(a.HighBit, b.HighBit);
			BOOST_CHECK_EQUAL(a.PixelSpacing, b.PixelSpacing);
			BOOST_CHECK_EQUAL(a.Range, b.Range);
			BOOST_CHECK_EQUAL(a.GetImagesNumber(), b.GetImagesNumber());
		}
	};

}
