#pragma once

#include "IImage.h"
#include "misOpenglTexture.h"

class misImageToTextureConvertor
{
private:
	double  m_tableRange[2];
public:
	misImageToTextureConvertor(void);
	~misImageToTextureConvertor(void);
	void SetTableRange(double* range);
	misOpenglTexture*   operator()(std::shared_ptr<IImage> image, bool isPolydata=false);
	misOpenglTexture*   operator()(std::shared_ptr<IImage> image, bool isPolydata , double* tableRange);
};
