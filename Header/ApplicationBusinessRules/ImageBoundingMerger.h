#pragma once
#include "IImageBoundingMerger.h"

namespace parcast
{

	class ImageBoundingMerger : public IImageBoundingMerger
	{

	public:

		ImageBoundingProperty Merge(std::shared_ptr<IImage> image1, std::shared_ptr<IImage> image2) override;

	};

}