#pragma once
#include "misGuiStructures.h"
#include "IVolumeThresholdUiUpdater.h"

class IDataUploadingUIADapter :  public IVolumeThresholdUiUpdater
{

public:
	virtual ~IDataUploadingUIADapter(){}
	virtual void UpdateDicomPropertiesEvent(const misDicomDataViewingProperties& viewingProp) = 0;
	virtual void LoadedDicomListEventCore(ImageViewingListTypedef imageList) = 0;

};
