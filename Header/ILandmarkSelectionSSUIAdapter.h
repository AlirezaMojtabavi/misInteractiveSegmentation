#pragma once
#include "misobjectProperitiesEnums.h" 
#include "misObjectRangeStr.h" 
#include "misVolumeViewingTypes.h"

class ILandmarkSelectionSSUIAdapter
{
public:
	virtual ~ILandmarkSelectionSSUIAdapter() = default;
	virtual void UpdateThresholdSlider(double normalizedValue, misObjectRangeStr foundRange) = 0;
	virtual void SaveSoloution() = 0;
	virtual void BackToPanStateEventCore() = 0;
	virtual void SendVolumeTypeEvent(misVolumeViewingTypes) = 0;
	virtual void SendImageModalityEvent(misImageDataModality modality) = 0;
	virtual void RegistrationLandmarkSelectionIDChanged(unsigned int landmarkIndex) = 0;
};
