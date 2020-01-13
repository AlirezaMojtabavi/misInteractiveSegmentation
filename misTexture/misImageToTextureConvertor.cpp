#include "stdafx.h"
#include "misImageToTextureConvertor.h"

#include "IImage.h"
#include "misImageByteAnalysis.h"
#include "misImageToTexturePropertyConvertor.h"
#include "misOpenglTexture.h"

misImageToTextureConvertor::misImageToTextureConvertor(void)
{
	m_tableRange[0]=-1;
	m_tableRange[1]=-1;
}

misImageToTextureConvertor::~misImageToTextureConvertor(void)
{
}

misOpenglTexture* misImageToTextureConvertor::operator()(std::shared_ptr<IImage> image, bool isPolydata)
{
	misImageToTexturePropertyConvertor convertor;
	tgt::Texture::Filter filter;
	if (isPolydata)
		filter = tgt::Texture::NEAREST ;
	else
		filter = tgt::Texture::LINEAR ;
	misTexturePropertyStruct texProp = convertor(image);
	misOpenglTexture* texture1 =  new misOpenglTexture(texProp,filter);
	texture1->setName(image->GetUID());
	texture1->SetImageUID(image->GetUID());
	return  texture1;
}

misOpenglTexture* misImageToTextureConvertor::operator()(std::shared_ptr<IImage> image, bool isPolydata, double* tableRange /*= 0 */)
{
	misImageToTexturePropertyConvertor convertor;
	misTexturePropertyStruct texProp = convertor(image);
	if (tableRange)
	{
		texProp.SetTableRane(tableRange);
	}
	
	tgt::Texture::Filter filter;
	if (isPolydata)
		filter = tgt::Texture::NEAREST ;
	else
		filter = tgt::Texture::LINEAR ;
	
	misOpenglTexture* texture1 =  new misOpenglTexture(texProp,filter);
	texture1->setName(image->GetUID());
	texture1->SetImageUID(image->GetUID());
	return  texture1;

}

void misImageToTextureConvertor::SetTableRange( double* range )
{
	m_tableRange[0]=range[0];
	m_tableRange[1]=range[1];
}
