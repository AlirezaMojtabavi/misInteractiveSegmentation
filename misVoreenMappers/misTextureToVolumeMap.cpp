#include "StdAfx.h"
#include "misTextureToVolumeMap.h"

using std::for_each;
using std::pair;

misTextureToVolumeMap::misTextureToVolumeMap(void)
{
}


misTextureToVolumeMap::~misTextureToVolumeMap(void)
{
}

misTextureToVolumeMap* misTextureToVolumeMap::GetInstance()
{
	static misTextureToVolumeMap* pInstance=new  misTextureToVolumeMap();
	return  pInstance;
}

void misTextureToVolumeMap::InsertPair( misOpenglTexture* texture,voreen::VolumeHandle* handle )
{

	m_TextureVolumeMap.push_back( pair<misOpenglTexture*,voreen::VolumeHandle*>(texture,handle));

}

std::deque<voreen::VolumeHandle*> misTextureToVolumeMap::LookUpVolume( misOpenglTexture* texture )
{

	std::deque<voreen::VolumeHandle*> results;

	//auto volume =m_TextureVolumeMap.find(texture);
	for_each(m_TextureVolumeMap.begin(),m_TextureVolumeMap.end(),[&](misTextureToVolumeMap::TextureVolumePair  element)
		
	{
		if (element.first==texture)
		{
			   results.push_back(element.second);
		}
		 
	}
	);
 
	return  results;

}
