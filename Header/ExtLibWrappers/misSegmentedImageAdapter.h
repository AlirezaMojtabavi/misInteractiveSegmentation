#pragma once

#include "ISegmentedImageDataAdapter.h"
#include "ImageContainedData.h"
#include "PackageImageContainedData.h"
#include "segmentedImageData.h"
#include "IImageContained.h"
#include "ICompeleteImageContainedPolydataDependensiesStrct.h"

class IDatasetManager;
class ISimpleDataPackage;
class misImageByteAnalysis;

namespace parcast
{

	class IDatasetIoWrapper;
	class IImageContainedDataAccess;
	class IImageContainedPropertiesDataAccess;
	class IPackageImageContainedDataAccess;
	class IPackageImageContainedVisibilityDataAccess;
	class ISegmentedImageDataAccess;

	template <typename ElemType, int Size>
	class IArrayBinaryCodec;

	class misSegmentedImageDataAdapter : public ISegmentedImageDataAdapter
	{
	public:
		misSegmentedImageDataAdapter(
			IDatasetManager* datasetManager,
			std::shared_ptr<ISegmentedImageDataAccess> SegmentedImageDataAccess,
			std::shared_ptr<IImageContainedDataAccess> imageContainedDataAccess,
			std::shared_ptr<IImageContainedPropertiesDataAccess> properties,
			std::shared_ptr<IPackageImageContainedDataAccess>pkgSegmentedImageRelDataAccess,
			std::shared_ptr<IPackageImageContainedVisibilityDataAccess> visibiltyDataAcces, 
			std::shared_ptr<IArrayBinaryCodec<int, 6>> extentCodec, 
			std::shared_ptr<IArrayBinaryCodec<double, 3>> spacingCodec,
			std::shared_ptr<IArrayBinaryCodec<double, 6>> roiCodec, 
			std::shared_ptr<IDatasetIoWrapper> rawBinaryAccess, 
			const std::string& rawImageDataPath);

		void Save() override;


		void Load() override;

	private:
		const int MinmumExpectedImageVolume = 125000;

		SegmentedImageData ConvertSegmentedImageToSegmentedImageData(
			std::shared_ptr<misImageByteAnalysis> SegmentedImage, std::string solutionUid) const;
		ImageContainedData ConvertImageContainedToImageContainedData(std::shared_ptr<IImageContained> SegmentedImage) const;


		PackageImageContainedData ConvertImageContainedeDepToPkgRelData(
			std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct> SegmentedImageDep, const std::string& packageUid) const;

		std::shared_ptr<misImageByteAnalysis> CreateSegmentedImageFromSegmentedImageData( const SegmentedImageData& ) const;
		std::shared_ptr<IImageContained> CreateImageContainedFromImageContainedData( const ImageContainedData&) const;

		std::shared_ptr<ICompeleteImageContainedPolydataDependensiesStrct> ConvertRelDataToImageContainedDep(
			 const PackageImageContainedData& relData, std::shared_ptr<ISimpleDataPackage> package, std::shared_ptr<IImageContained> SegmentedImage);


		IDatasetManager* m_DatasetManager;
		std::shared_ptr<ISegmentedImageDataAccess> m_SegmentedImageDataAccess;
		std::shared_ptr<IImageContainedDataAccess> m_ImageContainedDataAccess;
		
		std::shared_ptr<IImageContainedPropertiesDataAccess> m_ImageContainedPropertiesDataAccess;
		std::shared_ptr<IPackageImageContainedDataAccess> m_PkgImageContainedRelDataAccess;
		std::shared_ptr<IPackageImageContainedVisibilityDataAccess> m_VisibilityDataAccess;
		std::shared_ptr<parcast::IArrayBinaryCodec<int, 6>> m_ExtentCodec;
		std::shared_ptr<parcast::IArrayBinaryCodec<double, 3>> m_SpacingCodec;
		std::shared_ptr<parcast::IArrayBinaryCodec<double, 6>> m_RoiCodec;
		std::shared_ptr<parcast::IDatasetIoWrapper> m_RawBinaryAccess;
		std::string m_SaveRawDirPath;


	};
}
