#include "StdAfx.h"
#include "misImageToTextureMap.h"

#include "IImage.h"
#include "misImageContained.h"
#include "misImageToTextureConvertor.h"
#include "misOpenglTexture.h"
#include "misStringTools.h"

using namespace std;



misImageToTextureMap* misImageToTextureMap::GetInstance()
{
	static misImageToTextureMap* pInstance=new  misImageToTextureMap();
	return  pInstance;
}

misOpenglTexture* misImageToTextureMap::LookUpTexture( std::weak_ptr<IImage> pImage )
{
	auto image = pImage.lock();
	if (m_TextureMap.find(image) == m_TextureMap.end())
	{
		m_TextureMap.insert( pair<std::shared_ptr<IImage>, misTextureTimeStruct>(pImage, GenerateTexture(image)) );
	}
	else
	{
		if (NeedUpdate(image))
			Update(image);
	}
	return m_TextureMap.find(image)->second.pLoadTexture;
}

void misImageToTextureMap::ReleaseTexture(std::shared_ptr<IImage> pImage)
{
	auto found = m_TextureMap.find(pImage);
	if (found != m_TextureMap.end())
	{
		(*found).second.pLoadTexture->ReleaseTextureResource();
		m_TextureMap.erase(found);

	}
}

misTextureTimeStruct misImageToTextureMap::GenerateTexture( std::shared_ptr<IImage> pImage )
{
	_ASSERT(pImage!=NULL);

	misTextureTimeStruct pTextTime;
	if (0 == pImage)
	{
		cout<< "\n  IImage == 0 !!!!!!!!!!!! \n" ;
		return  	pTextTime;
	}
	bool isPoly=false;
	misImageToTextureConvertor  convertor;


	misImageByteAnalysis* pImageContained = dynamic_cast<misImageByteAnalysis*>(pImage.get());
	if (pImageContained)
	{
		isPoly=true;
		double tableRange[2];
		tableRange[0] = 0;
		//	tableRange[1] = 255.0;
		//	Graphic card can't support a texture of the width of 2^16. maxTexSize = GpuCaps.getMaxTextureSize() = 

		//2^14 = 16384;
		tableRange[1] =  pImageContained->GetRawImageData()->GetScalarTypeMax();   

		pTextTime.pLoadTexture=convertor(pImage, isPoly,tableRange); 
	}
	else
	{
		pTextTime.pLoadTexture=convertor(pImage, isPoly); 
		pTextTime.pLoadTexture->SetImageUID(pImage->GetUID());
	}

	pTextTime.pLoadTime.Modified();
	return pTextTime;

}

void misImageToTextureMap::ReleaseTexureResources()
{
	for_each(m_TextureMap.begin(), m_TextureMap.end(), [&](std::pair<std::shared_ptr<IImage>, misTextureTimeStruct> member)
	{
		member.second.pLoadTexture->ReleaseTextureResource();
	});

	m_TextureMap.clear();
}

misImageToTextureMap::misImageToTextureMap()
{
}

void misImageToTextureMap::Update( std::shared_ptr<IImage> pImage)
{

	misTextureTimeStruct textTime = m_TextureMap[pImage];
	textTime.pLoadTexture->ReleaseTextureResource();
	textTime = GenerateTexture(pImage);
	m_TextureMap[pImage]=textTime;

}

bool misImageToTextureMap::NeedUpdate( std::shared_ptr<IImage> pImage )
{
	unsigned long  timeInput=pImage->GetRawImageData()->GetMTime();
	unsigned long  timeGenerationTexture = timeInput+1;
	if (m_TextureMap.find(pImage) != m_TextureMap.end())
	{
		misTextureTimeStruct textTime = m_TextureMap[pImage];
		timeGenerationTexture=textTime.pLoadTime.GetMTime();
	}
	
	bool cond2 = timeInput>timeGenerationTexture;
	return cond2;
}



