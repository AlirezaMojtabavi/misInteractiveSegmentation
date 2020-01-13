#pragma once

#include "IImage.h"
#include "misOpenglTexture.h"

class IImageToTextureMap
{
public:
	virtual misOpenglTexture* LookUpTexture(std::weak_ptr<IImage> pImage) = 0;
	virtual void ReleaseTexture(std::shared_ptr<IImage> pImage) = 0;
	virtual void ReleaseTexureResources() = 0;
	virtual bool NeedUpdate(std::shared_ptr<IImage> pImage) = 0;
	virtual void Update(std::shared_ptr<IImage> pImage) = 0;
};
