#pragma once

#include "IImageDataAdapter.h"
#include "ImageData.h"

class IDatasetManager;
class IImage;

namespace parcast
{
	template <typename ElemType, int Size>
	class IArrayBinaryCodec;

	class ICoordinateSystemDataAccess;
	class ICorrelationDataAccess;
	class IDatasetIoWrapper;
	class IImageDataAccess;
	class IImageFactory;
	class IPackageImageRelDataAccess;
	class IVtkTransMatBinaryCodec;
}

class misImageDataAdapter : public parcast::IImageDataAdapter
{
public:
	misImageDataAdapter(
		IDatasetManager* datasetManager, std::shared_ptr<parcast::IImageDataAccess> imageDA,
		std::shared_ptr<parcast::IPackageImageRelDataAccess> imPacRelDa,
		std::shared_ptr<parcast::ICorrelationDataAccess> correlationDA,
		std::shared_ptr<parcast::ICoordinateSystemDataAccess> coordinateSysDA,
		std::shared_ptr<parcast::IVtkTransMatBinaryCodec> VtkCodec,
		std::shared_ptr<parcast::IArrayBinaryCodec<int, 6>> extentCodec,
		std::shared_ptr<parcast::IArrayBinaryCodec<double, 3>> spacingCodec,
		std::shared_ptr<parcast::IArrayBinaryCodec<double, 6>> roiCodec,
		std::shared_ptr<parcast::IArrayBinaryCodec<float, 3>> pixelSpacingCodec,
		std::shared_ptr<parcast::IImageFactory> imageFactory,
		std::shared_ptr<parcast::IDatasetIoWrapper> rawBinaryAccess, const std::string& path);

	void SaveImages() const override;
	void LoadImages() const override;

private:
	const int MinmumExpectedImageVolume = 125000;

	void CheckForDeletedImages(const std::string& currentSolutionUid) const;

	parcast::ImageData ConvertFromImageToImageData(
		const std::vector<std::shared_ptr<IImage>>::value_type& image, const std::string& solutionUid) const;

	std::shared_ptr<IImage> ConvertImageDataToImage(const parcast::ImageData& imageData) const;
	std::set<std::string> GetImageUidsFromDatasetManager() const;

	IDatasetManager* m_DatasetManager;
	std::shared_ptr<parcast::IImageDataAccess> m_ImageDataAccess;
	std::shared_ptr<parcast::IPackageImageRelDataAccess> m_ImgPkgRelDataAccess;
	std::shared_ptr<parcast::ICoordinateSystemDataAccess> m_CoordinateSysDataAccess;
	std::shared_ptr<parcast::ICorrelationDataAccess> m_CorrelationDataAccess;

	std::shared_ptr<parcast::IVtkTransMatBinaryCodec> m_VtkTransCodec;
	std::shared_ptr<parcast::IArrayBinaryCodec<int, 6>> m_ExtentCodec;
	std::shared_ptr<parcast::IArrayBinaryCodec<double, 3>> m_SpacingCodec;
	std::shared_ptr<parcast::IArrayBinaryCodec<double, 6>> m_RoiCodec;
	std::shared_ptr<parcast::IArrayBinaryCodec<float, 3>> m_PixelSpacingCodec;

	std::shared_ptr<parcast::IImageFactory> m_ImageFactory;
	std::shared_ptr<parcast::IDatasetIoWrapper> m_RawBinaryAccess;
	std::string m_SaveRawDirPath;
};
