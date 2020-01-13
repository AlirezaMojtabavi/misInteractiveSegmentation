#pragma once

#include "IImageToTextureMap.h"

MOCK_BASE_CLASS(MockImageToTextureMap, IImageToTextureMap)
{
	MOCK_NON_CONST_METHOD(LookUpTexture, 1, misOpenglTexture*(std::weak_ptr<IImage> pImage));
	MOCK_NON_CONST_METHOD(ReleaseTexture, 1, void(std::shared_ptr<IImage> pImage));
	MOCK_NON_CONST_METHOD(ReleaseTexureResources, 0, void());
	MOCK_NON_CONST_METHOD(NeedUpdate, 1, bool(std::shared_ptr<IImage> pImage));
	MOCK_NON_CONST_METHOD(Update, 1, void(std::shared_ptr<IImage> pImage));
};

