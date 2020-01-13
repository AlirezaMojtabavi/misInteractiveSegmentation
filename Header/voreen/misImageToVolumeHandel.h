#pragma once

#include "misImage.h"
#include "misOpenglTexture.h"

class misImageToVolumeHandel
{
private:
	void UpdateRoi( misOpenglTexture* pTexture, voreen::VolumeHandle* vHandle );
public:
	misImageToVolumeHandel(void);
	~misImageToVolumeHandel(void);
	voreen::VolumeHandle* ConvertTexture(std::shared_ptr<misImage> pImage);
	voreen::VolumeHandle* ConvertTexture(misOpenglTexture* pTexture);
	voreen::VolumeHandle* GenerateVolume( int type, misOpenglTexture * texture1 );
	voreen::VolumeHandle* GenerateShortVolume( misOpenglTexture * texture1 );
	voreen::VolumeHandle* GenerateCharVolume( misOpenglTexture * texture1 );

};

