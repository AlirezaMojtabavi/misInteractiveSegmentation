#pragma once
#include "IImageCorrelationTempCompositePackageCreator.h"

namespace parcast
{

	class ImageCorrelationTempCompositePackageCreator : public IImageCorrelationTempCompositePackageCreator
	{
	public:
		std::shared_ptr<ISimpleDataPackage> Create(
			std::shared_ptr<IImage> fixedImage, std::shared_ptr<IImage> movingImage,
			const misColorStruct& fixedColor, const misColorStruct& movingColor,
			double fixedImageOpacity, double movingImageOpacity) const override;

	private:

		void CreateTemporaryVolumeDependency(
			std::shared_ptr<ISimpleDataPackage> package,
			std::shared_ptr<IImage> tempImage, const misColorStruct& tempColor,
			double tempOpacity) const;

		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> m_CorrelationManager;
	};

}
