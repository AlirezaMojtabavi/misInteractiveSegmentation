#pragma once

#include "IImage.h"
#include "ImageBoundingProperty.h"

namespace parcast
{

	class IImageBoundingMerger
	{

	public:
		virtual ImageBoundingProperty Merge(std::shared_ptr<IImage> image1, std::shared_ptr<IImage> image2) = 0;

	};

}