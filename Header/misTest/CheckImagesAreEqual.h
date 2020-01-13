#pragma once

#include "IImage.h"
#include "misImageIOProperties.h"
#include "BusinessEntities/Point.h"

#define REPORTFAILED(A) OutputResult(A, #A)

namespace parcast
{

	class CheckImagesAreEqual
	{
	public:
		static bool Check(std::shared_ptr<IImage> a, std::shared_ptr<IImage> b)
		{
			auto result = true;
			result = result && REPORTFAILED(a->GetPrimeryUID() == b->GetPrimeryUID());
			auto dimsA = a->GetRawImageData()->GetDimensions(), dimsB = b->GetRawImageData()->GetDimensions();
			auto sizeA = a->GetRawImageData()->GetScalarSize(), sizeB = b->GetRawImageData()->GetScalarSize();
			auto numScalarsA = a->GetRawImageData()->GetNumberOfScalarComponents();
			auto numScalarsB = b->GetRawImageData()->GetNumberOfScalarComponents();
			result = result && REPORTFAILED(std::equal(dimsA, dimsA + 3, dimsB));
			result = result && REPORTFAILED(sizeA == sizeB);
			result = result && REPORTFAILED(numScalarsA == numScalarsB);

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
			result = result && REPORTFAILED(rawImageEqual);

			result = result && REPORTFAILED(CheckMisDicomDataViewingProperties(a->GetSimplifiedProperties(), b->GetSimplifiedProperties()));
			auto spacingA = a->GetSpacing(), spacingB = b->GetSpacing();
			result = result && REPORTFAILED(std::equal(spacingA, spacingA + 3, spacingB, spacingB + 3));
			result = result && REPORTFAILED(a->GetName() == b->GetName());
			result = result && REPORTFAILED(a->GetObjectType() == b->GetObjectType());
			result = result && REPORTFAILED(a->GetScalarType() == b->GetScalarType());
			result = result && REPORTFAILED(a->GetViewingNameCompletenessStatus() == b->GetViewingNameCompletenessStatus());
			result = result && REPORTFAILED(a->GetConfirmedDirection() == b->GetConfirmedDirection());
			result = result && REPORTFAILED(a->GetImageModality() == b->GetImageModality());
			result = result && REPORTFAILED(a->GetParentImageUID() == b->GetParentImageUID());
			result = result && REPORTFAILED(a->GetDuplicatedRangeActivation() == b->GetDuplicatedRangeActivation());

			result = result && REPORTFAILED(CheckMisImageRoi(a->GetROI(), b->GetROI()));
			result = result && REPORTFAILED(CheckMisImageRoi(a->GetWorldDiemension(), b->GetWorldDiemension()));

			auto scalarRangeNeededA = a->GetScalerRangeNeeded(), scalarRangeNeededB = b->GetScalerRangeNeeded();
			result = result && REPORTFAILED(scalarRangeNeededA == scalarRangeNeededB);
			result = result && REPORTFAILED(CheckEqualMisImageIOProperties(a->GetImageIOProperties(), b->GetImageIOProperties()));
			result = result && REPORTFAILED(CheckEqualMisImageDataProperties(*a->GetImageDataProperties(), *b->GetImageDataProperties()));
			result = result && REPORTFAILED(CheckEqualMisImageViewingItemsStruct(a->GetViewingStrct(), b->GetViewingStrct()));
			result = result && REPORTFAILED(std::equal(a->GetDimensions(), a->GetDimensions() + 3, b->GetDimensions()));

			auto imageCenterA = a->GetImageCenter();
			auto imageCenterB = b->GetImageCenter();
			result = result && REPORTFAILED(std::equal(imageCenterA.Elements(), imageCenterA.Elements()+ 3 , imageCenterB.Elements()));
			return result;
		}

		static bool OutputResult(bool check, const char* line)
		{
			if (!check)
				std::cout << line << "=" << check << std::endl;

			return check;
		}
	private:

		static bool CheckMisDicomDataViewingProperties(const misDicomDataViewingProperties& a, const misDicomDataViewingProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(CheckMisViewingPatientProperties(a.patientProperties, b.patientProperties));
			result = result && REPORTFAILED(CheckMisViewingImageProperties(a.imageProperties, b.imageProperties));
			result = result && REPORTFAILED(CheckMisStudySerieViewingProperties(a.studySerieProperties, b.studySerieProperties));
			return result;
		}

		static bool CheckEqualMisImageViewingItemsStruct(const misImageViewingItemsStruct& a, const misImageViewingItemsStruct& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.viewingName == b.viewingName);
			result = result && REPORTFAILED(a.name == b.name);
			result = result && REPORTFAILED(a.description == b.description);
			result = result && REPORTFAILED(a.numberofImages == b.numberofImages);
			result = result && REPORTFAILED(a.modality == b.modality);
			result = result && REPORTFAILED(a.Dimention == b.Dimention);
			result = result && REPORTFAILED(a.Spacing == b.Spacing);
			result = result && REPORTFAILED(a.objectUID == b.objectUID);
			result = result && REPORTFAILED(a.packageUID == b.packageUID);
			result = result && REPORTFAILED(a.directionSataus == b.directionSataus);
			result = result && REPORTFAILED(a.correlationSatus == b.correlationSatus);
			result = result && REPORTFAILED(a.visibilitySatus == b.visibilitySatus);
			result = result && REPORTFAILED(a.makeCompleteName == b.makeCompleteName);
			return result;
		}

		static bool CheckMisImageRoi(const misROI& a, const misROI& b)
		{
			double d1[6], d2[6];
			a.getData(d1);
			b.getData(d2);
			auto result = true;
			result = result && REPORTFAILED(std::equal(d1, d1 + 6, d2));
			result = result && REPORTFAILED(a.IsInitilized() == b.IsInitilized());
			result = result && REPORTFAILED(a.IsPermanent() == b.IsPermanent());
			result = result && REPORTFAILED(a.GetVolume() == b.GetVolume());
			result = result && REPORTFAILED(a.IsValid() == b.IsValid());
			result = result && REPORTFAILED(a.GetWidth() == b.GetWidth());
			result = result && REPORTFAILED(a.GetHeight() == b.GetHeight());
			result = result && REPORTFAILED(a.GetDepth() == b.GetDepth());
			result = result && REPORTFAILED(a.GetMinPoint() == b.GetMinPoint());
			result = result && REPORTFAILED(a.GetMaxPoint() == b.GetMaxPoint());
			return result;
		}

		static bool CheckMisViewingPatientProperties(const misViewingPatientProperties& a, const misViewingPatientProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.FamilyName == b.FamilyName);
			result = result && REPORTFAILED(a.Gender == b.Gender);
			result = result && REPORTFAILED(a.BirthData == b.BirthData);
			result = result && REPORTFAILED(a.Weight == b.Weight);
			result = result && REPORTFAILED(a.Age == b.Age);
			return result;
		}

		static bool CheckMisViewingImageProperties(const misViewingImageProperties& a, const misViewingImageProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.ImageModality == b.ImageModality);
			result = result && REPORTFAILED(a.ProtocolName == b.ProtocolName);
			result = result && REPORTFAILED(a.NumberofImages == b.NumberofImages);
			result = result && REPORTFAILED(a.ZResolution == b.ZResolution);
			result = result && REPORTFAILED(a.Rows == b.Rows);
			result = result && REPORTFAILED(a.Columns == b.Columns);
			return result;
		}

		static bool CheckMisStudySerieViewingProperties(const misStudySerieViewingProperties& a, const misStudySerieViewingProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.SeriesDescription == b.SeriesDescription);
			result = result && REPORTFAILED(a.SerieAcquisitionDate == b.SerieAcquisitionDate);
			result = result && REPORTFAILED(a.SerieAcquisitionTime == b.SerieAcquisitionTime);
			result = result && REPORTFAILED(a.StudyDescription == b.StudyDescription);
			result = result && REPORTFAILED(a.StudyDate == b.StudyDate);
			return result;
		}

		static bool CheckEqualMisImageIOProperties(const misImageIOProperties& a, const misImageIOProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.NumberOfComponent == b.NumberOfComponent);
			result = result && REPORTFAILED(std::equal(a.extent, a.extent + 6, b.extent));
			result = result && REPORTFAILED(std::equal(a.spacing, a.spacing + 3, b.spacing));
			result = result && REPORTFAILED(a.scalerType == b.scalerType);
			result = result && REPORTFAILED(a.fileDimensionality == b.fileDimensionality);
			result = result && REPORTFAILED(std::equal(a.FOVExtent, a.FOVExtent + 6, b.FOVExtent));
			result = result && REPORTFAILED(CheckMisImageRoi(a.GetRoi(), b.GetRoi()));
			return result;
		}

		static bool CheckEqualMisImageDataProperties(const misImageDataProperties& a, const misImageDataProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.GetCurrentThresholdForSkinViewing() == b.GetCurrentThresholdForSkinViewing());
			result = result && REPORTFAILED(a.GetDefaultThresholdForSkinViewing() == b.GetDefaultThresholdForSkinViewing());
			result = result && REPORTFAILED(a.GetViewingNameType() == b.GetViewingNameType());
			result = result && REPORTFAILED(CheckMisWindowLevelStr(a.GetWindowlevel(), b.GetWindowlevel()));
			result = result && REPORTFAILED(a.GetCurrentThresholdForBoneViewing() == b.GetCurrentThresholdForBoneViewing());
			result = result && REPORTFAILED(a.GetCurrentThresholdForTeethViewing() == b.GetCurrentThresholdForTeethViewing());
			result = result && REPORTFAILED(a.GetColorMapType() == b.GetColorMapType());
			result = result && REPORTFAILED(CheckEqualMisImageViewingProperties(a.GetViewingProperties(), b.GetViewingProperties()));
			result = result && REPORTFAILED(CheckEqualMisImageingProperties(a.imagingProprties, b.imagingProprties));
			result = result && REPORTFAILED(CheckEqualMisPatientProperties(a.patientProperties, b.patientProperties));
			result = result && REPORTFAILED(CheckEqualMisHardwareProperties(a.hardwareProperties, b.hardwareProperties));
			result = result && REPORTFAILED(CheckMisSerieProperties(a.serieProperties, b.serieProperties));
			result = result && REPORTFAILED(CheckEqualMisStudyProperties(a.studyProperties, b.studyProperties));
			result = result && REPORTFAILED(CheckEqualMisImageProperties(a.imageProperties, b.imageProperties));
			return result;
		}

		static bool CheckMisWindowLevelStr(const misWindowLevelStr& a, const misWindowLevelStr& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.GetWindowCenter() == b.GetWindowCenter());
			result = result && REPORTFAILED(a.GetWindowWidth() == b.GetWindowWidth());
 			return result;
		}

		static bool CheckEqualMisImageViewingProperties(const misImageViewingProperties& a, const misImageViewingProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.GetCurrentThresholdForSkinViewing() == b.GetCurrentThresholdForSkinViewing());
			result = result && REPORTFAILED(a.GetCurrentThresholdForBoneViewing() == b.GetCurrentThresholdForBoneViewing());
			result = result && REPORTFAILED(a.GetCurrentThresholdForTeethViewing() == b.GetCurrentThresholdForTeethViewing());
			result = result && REPORTFAILED(a.GetCurrentThresholdForSkinFilledViewing() == b.GetCurrentThresholdForSkinFilledViewing());
			result = result && REPORTFAILED(CheckMisWindowLevelStr(a.GetLevelWindow(), b.GetLevelWindow()));
			result = result && REPORTFAILED(a.GetViewingNameType() == b.GetViewingNameType());
			result = result && REPORTFAILED(a.GetColorMapType() == b.GetColorMapType());
			result = result && REPORTFAILED(CheckMisWindowLevelStr(a.GetInitialLevelWindow(), b.GetInitialLevelWindow()));
			return result;
		}

		static bool CheckEqualMisImageingProperties(const misImageingProperties& a, const misImageingProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.ImageModality == b.ImageModality);
			result = result && REPORTFAILED(a.ProtocolName == b.ProtocolName);
			result = result && REPORTFAILED(CheckEqualMisCTImageingProperties(a.CTDATA, b.CTDATA));
			result = result && REPORTFAILED(CheckEqualMisMRImageingProperties(a.MRDATA, b.MRDATA));
			return result;
		}

		static bool CheckEqualMisCTImageingProperties(const misCTImageingProperties& a, const misCTImageingProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.DistanceSourcetoDetector == b.DistanceSourcetoDetector);
			//result = result &&  REPORTFAILED (a.DistanceSourcetoPatient == b.DistanceSourcetoPatient);
			result = result && REPORTFAILED(a.ExposureTime == b.ExposureTime);
			result = result && REPORTFAILED(a.X_RayTubeCurrent == b.X_RayTubeCurrent);
			result = result && REPORTFAILED(a.Exposure == b.Exposure);
			result = result && REPORTFAILED(a.KV == b.KV);
			result = result && REPORTFAILED(a.KV == b.KV);
			return result;
		}

		static bool CheckEqualMisMRImageingProperties(const misMRImageingProperties& a, const misMRImageingProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.PhaseEncoding == b.PhaseEncoding);
			result = result && REPORTFAILED(a.FlipAngle == b.FlipAngle);
			result = result && REPORTFAILED(a.VariableFlipAngle == b.VariableFlipAngle);
			result = result && REPORTFAILED(a.PixelBandWidth == b.PixelBandWidth);
			result = result && REPORTFAILED(a.EchoNumber == b.EchoNumber);
			result = result && REPORTFAILED(a.ImageFrequency == b.ImageFrequency);
			result = result && REPORTFAILED(a.PercentPhaseFieldofView == b.PercentPhaseFieldofView);
			result = result && REPORTFAILED(a.RepetitionTime == b.RepetitionTime);
			result = result && REPORTFAILED(a.SpatialResolution == b.SpatialResolution);
			return result;
		}

		static bool CheckEqualMisPatientProperties(const misPatientProperties& a, const misPatientProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.GetAge() == b.GetAge());
			result = result && REPORTFAILED(a.GetBirthDate() == b.GetBirthDate());
			result = result && REPORTFAILED(a.NationalCode == b.NationalCode);
			result = result && REPORTFAILED(a.FirstName == b.FirstName);
			result = result && REPORTFAILED(a.Gender == b.Gender);
			result = result && REPORTFAILED(a.Weight == b.Weight);
			result = result && REPORTFAILED(a.Position == b.Position);
			result = result && REPORTFAILED(a.ReadyForSurgery == b.ReadyForSurgery);
			return result;
		}

		static bool CheckEqualMisHardwareProperties(const misHardwareProperties& a, const misHardwareProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.Manufacturer == b.Manufacturer);
			result = result && REPORTFAILED(a.ManufacturerModelName == b.ManufacturerModelName);
			result = result && REPORTFAILED(a.SoftwareVersion == b.SoftwareVersion);
			result = result && REPORTFAILED(a.InstitutionName == b.InstitutionName);
			return result;
		}

		static bool CheckMisSerieProperties(const misSerieProperties& a, const misSerieProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.SeriesDescription == b.SeriesDescription);
			result = result && REPORTFAILED(a.AcquisitionDate == b.AcquisitionDate);
			result = result && REPORTFAILED(a.AcquisitionTime == b.AcquisitionTime);
			//result = result &&  REPORTFAILED (a.SerieUID, b.SerieUID);
			return result;
		}

		static bool CheckEqualMisStudyProperties(const misStudyProperties& a, const misStudyProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.StudyDescription == b.StudyDescription);
			result = result && REPORTFAILED(a.StudyDate == b.StudyDate);
			result = result && REPORTFAILED(a.StudyTime == b.StudyTime);
			//result = result &&  REPORTFAILED (a.StudyUID, b.StudyUID);
			return result;
		}

		static bool CheckEqualMisImageProperties(const misImageProperties& a, const misImageProperties& b)
		{
			auto result = true;
			result = result && REPORTFAILED(a.SamplesperPixel == b.SamplesperPixel);
			result = result && REPORTFAILED(a.Rows == b.Rows);
			result = result && REPORTFAILED(a.Columns == b.Columns);
			result = result && REPORTFAILED(a.BitsAllocated == b.BitsAllocated);
			result = result && REPORTFAILED(a.BitsStored == b.BitsStored);
			result = result && REPORTFAILED(a.HighBit == b.HighBit);
			result = result && REPORTFAILED(a.PixelSpacing == b.PixelSpacing);
			result = result && REPORTFAILED(a.Range == b.Range);
			result = result && REPORTFAILED(a.GetImagesNumber() == b.GetImagesNumber());
			return result;
		}
	};

}
