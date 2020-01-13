#pragma once

#include "misTexturePropertyStruct.h"

class IImage;

class misImageToTexturePropertyConvertor
{
public:
	misImageToTexturePropertyConvertor();
	misTexturePropertyStruct operator()(std::shared_ptr<IImage> image);

private:
	misTexturePropertyStruct m_texProp;
	void SetTableRange(std::shared_ptr<IImage> input);
	void SetModality(std::shared_ptr<IImage> image);
	void SetBitStored(std::shared_ptr<IImage> input);
	void SetSpacing(std::shared_ptr<IImage> input);
	void SetOrigin(std::shared_ptr<IImage> input);
	void SetExtent(std::shared_ptr<IImage> input);
};
