#pragma once

#include "IImageFactory.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockImageFactory, IImageFactory)
	{
		MOCK_CONST_METHOD(CreateImage, 0, std::shared_ptr<IImage>());
	};

}
