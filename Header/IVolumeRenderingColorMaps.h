#pragma once
#include "misImageModalityEnum.h"
#include "misobjectProperitiesEnums.h"
#include "misColorStruct.h"
#include "misVolumeViewingTypes.h"

class IVolumeRenderingColorMaps
{
public:
	
	// Set Image acquisition modality (e.g. CT, MRI, PET, ...) please see misImageDataModality for complete list of modalities
	virtual void SetImageModality(misImageDataModality imageModality) = 0;

	// Set Volume type (e.g. Skin, Bone, ...) please see misVolumeViewingTypes for complete list of modalities
	virtual void SetObjectType(misVolumeViewingTypes volumeType) = 0;

	// Set Minimum/maximum threshold for representing the range of intensity for the specified object
	virtual void SetObjectThreshold(double minThreshold) = 0;

	// Set the Color and Opacity of specified Object to the default value
	virtual void SetObjectColorDefault(void) = 0;


	// Set/Get the Color and Opacity of specified Object 
	virtual misColorStruct GetObjectColor(void) = 0;
		
	virtual void SetObjectThresholdDefault(void) = 0;

	virtual void SetObjectColor(const misColorStruct& objectColor) = 0;
	
	virtual misColorListTypedef GetVolumeColorMap(void) = 0;

	virtual std::unique_ptr<IVolumeRenderingColorMaps> clone() = 0;
};

