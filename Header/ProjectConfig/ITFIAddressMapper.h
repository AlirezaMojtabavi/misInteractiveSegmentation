#pragma once

#include "misImageModalityEnum.h"
#include "misobjectProperitiesEnums.h"
#include "misVolumeViewingTypes.h"

// This class maps address of corresponding XML file contains trans function to the image modalities and viewing type.
class ITFIAddressMapper
{
public:
	// Set a file name to the corresponding modality and viewing.
	virtual void SetTFIFileName(misImageDataModality modality, misVolumeViewingTypes viewingType, const std::string& fileName) = 0;

	// Get a file name of the requested modality and viewing.
	virtual std::string GetTFIFileName(misImageDataModality modality, misVolumeViewingTypes viewingType) const = 0;

	virtual ~ITFIAddressMapper() { };
};