#pragma once
#include "misCompositeDataPackage.h"

namespace parcast
{

	class IImageCorrelationTempCompositePackageCreator
	{
	public:
		virtual std::shared_ptr<ISimpleDataPackage> Create(
			std::shared_ptr<IImage> fixedImage, std::shared_ptr<IImage> movingImage,
			const misColorStruct& fixedColor, const misColorStruct& movingColor,
			double fixedImageOpacity, double movingImageOpacity) const = 0;
	};

}
