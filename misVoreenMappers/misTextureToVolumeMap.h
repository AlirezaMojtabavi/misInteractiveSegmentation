#pragma once

#include "misOpenglTexture.h"

class misTextureToVolumeMap
{
private:
		typedef std::pair<misOpenglTexture*,voreen::VolumeHandle*>  TextureVolumePair;
		std::deque<TextureVolumePair>	m_TextureVolumeMap;
		misTextureToVolumeMap(void);
public:

	static misTextureToVolumeMap*	GetInstance();
	void InsertPair(misOpenglTexture* texture,voreen::VolumeHandle* handle);
	std::deque<voreen::VolumeHandle*>  LookUpVolume(misOpenglTexture* texture);


	~misTextureToVolumeMap(void);
};

