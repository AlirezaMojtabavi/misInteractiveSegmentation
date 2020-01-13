#include "StdAfx.h"
#include "misTextureTimeStruct.h"

#include "misOpenglTexture.h"

misTextureTimeStruct::misTextureTimeStruct(void)
{
	pLoadTexture=NULL;
}


misTextureTimeStruct::~misTextureTimeStruct(void)
{
	if (pLoadTexture)
	{
		//TODO:use  samrt pointer
		//delete  pLoadTexture;
	}
}
