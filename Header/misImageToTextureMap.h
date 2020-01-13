#pragma once

#include "..\misTexture\misTextureTimeStruct.h"
#include "IImage.h"
#include "IImageToTextureMap.h"

class IImage;
class misOpenglTexture;

// The misImageToTextureMap is a repository for all GPU textures used by the application. When reading a new patient is created,
// all resources belonging to the last patient must be released.
class misImageToTextureMap :public IImageToTextureMap
{
public:
	static misImageToTextureMap* GetInstance() ;

	misOpenglTexture* LookUpTexture( std::weak_ptr<IImage> pImage ) override;
	void ReleaseTexture(std::shared_ptr<IImage> pImage) override;

	// Release all texure resource
	void ReleaseTexureResources() override;

	bool NeedUpdate( std::shared_ptr<IImage> pImage ) override;
	void Update( std::shared_ptr<IImage> pImage ) override;
	

private:
	misImageToTextureMap();

	std::map<std::shared_ptr<IImage>, misTextureTimeStruct> m_TextureMap;
	misTextureTimeStruct GenerateTexture( std::shared_ptr<IImage> pImage );
};
