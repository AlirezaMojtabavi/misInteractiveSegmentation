#pragma once

#include "IImageFactory.h"

namespace parcast
{

	class ImageFactory : public IImageFactory
	{
	public:
		virtual std::shared_ptr<IImage> CreateImage() const override;
	};

}
