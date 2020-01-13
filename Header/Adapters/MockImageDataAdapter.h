#pragma once
#include "IImageDataAdapter.h"
#include<turtle/mock.hpp>
namespace parcast
{
	MOCK_BASE_CLASS(MockImageDataAdapter, IImageDataAdapter)
	{
		MOCK_CONST_METHOD(SaveImages, 0, void(void));
	};
}