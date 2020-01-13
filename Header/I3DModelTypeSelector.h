#pragma once
#include "ApproachAndModelInformationStrct.h"
#include "misImageModalityenum.h"
#include "misVolumeViewingTypes.h"

class I3DModelTypeSelector
{
public:
	virtual ~I3DModelTypeSelector() = default;
	virtual  mis3DModelTypes GetMOdelType(misImageDataModality modality, misVolumeViewingTypes volumeType) const = 0;
	
};
