#include "StdAfx.h"
#include "misImageToVolumeHandel.h"

#include "misDIRReader.h"
#include "misImageToTexturePropertyConvertor.h"
#include "misOpenglTexture.h"
#include "misStrctDicomIO.h"
#include "misTexturePropertyStruct.h"
#include "misTextureToVolumeMap.h"

misImageToVolumeHandel::misImageToVolumeHandel(void)
{
}


misImageToVolumeHandel::~misImageToVolumeHandel(void)
{
}

voreen::VolumeHandle* misImageToVolumeHandel::ConvertTexture(std::shared_ptr<misImage> pImage)
{	
	misImageToTexturePropertyConvertor Convertor;
	misTexturePropertyStruct Prop = Convertor(pImage);
	misOpenglTexture* texture = new misOpenglTexture(Prop,tgt::Texture::LINEAR);
	int type = pImage->GetRawImageData()->GetScalarType();
	voreen::VolumeHandle*  vHandle = GenerateVolume(type , texture);
	UpdateRoi(texture,vHandle); 
	
	return vHandle; 
}

voreen::VolumeHandle* misImageToVolumeHandel::ConvertTexture( misOpenglTexture* pTexture )
{
	int type = pTexture->GetTexturePropertyStrct().DataType;
	voreen::VolumeHandle*  vHandle = GenerateVolume(type , pTexture);
	UpdateRoi(pTexture, vHandle);

	return vHandle; 
}

voreen::VolumeHandle* misImageToVolumeHandel::GenerateShortVolume( misOpenglTexture * texture1 )
{
	tgt::ivec3  dim = texture1->GetTexturePropertyStrct().GetDimensions();
	tgt::vec3  spacing=texture1->GetTexturePropertyStrct().Spacing;
	short *data = (short *) texture1->GetTexturePropertyStrct().Data;
	tgt::mat4 transformationMatrix = tgt::mat4::createIdentity();

 	voreen::VolumeAtomic<short>* volume;

	
	volume = new voreen::VolumeAtomic<short>(data,dim,spacing,transformationMatrix,sizeof(short)); 	
	volume->setTexture(texture1);
	voreen::VolumeHandle* vHandle = new voreen::VolumeHandle();
	vHandle->setVolume(volume);
	UpdateRoi(texture1,vHandle);
	return  vHandle;
}

voreen::VolumeHandle* misImageToVolumeHandel::GenerateCharVolume( misOpenglTexture * texture1 )
{
	tgt::ivec3  dim=texture1->GetTexturePropertyStrct().GetDimensions();
	tgt::vec3  spacing=texture1->GetTexturePropertyStrct().Spacing;
	unsigned char *data = (unsigned char *) texture1->GetTexturePropertyStrct().Data;
	tgt::mat4 transformationMatrix = tgt::mat4::createIdentity();
	
	
	voreen::VolumeAtomic<unsigned char>* volume = new voreen::VolumeAtomic<unsigned char>(data,dim,spacing,transformationMatrix,sizeof(unsigned char)); 
	volume->setTexture(texture1);
	voreen::VolumeHandle* vHandle = new voreen::VolumeHandle();
	vHandle->setVolume(volume);
	UpdateRoi(texture1,vHandle);
	return  vHandle;
}

voreen::VolumeHandle* misImageToVolumeHandel::GenerateVolume( int type, misOpenglTexture * texture )
{
	voreen::VolumeHandle*  vHandle = NULL;

	if (type == GL_UNSIGNED_SHORT || type == GL_SHORT )
	{
	  vHandle=GenerateShortVolume(texture);
	}
	else if (type == GL_UNSIGNED_BYTE || type == GL_BYTE )
	{
	   vHandle=GenerateCharVolume(texture);	
	}
	return vHandle;
}

void misImageToVolumeHandel::UpdateRoi( misOpenglTexture* pTexture, voreen::VolumeHandle* vHandle )
{
	misTextureToVolumeMap* textVolMapp=misTextureToVolumeMap::GetInstance();
	textVolMapp->InsertPair(pTexture, vHandle);
	misROI roi = pTexture->GetROI();
	if (roi.IsInitilized())
	{
		double roiData[6];
		roi.getData(roiData);
		vHandle->getVolume()->SetROI(roiData);
	}
}

