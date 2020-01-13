#pragma once
#include "misobjectProperitiesEnums.h"
#include "IImage.h"
#include "ISimpleDataPackage.h"
#include "misVolumeViewingTypes.h"

class IVolumeUpdater
{
public:
	virtual ~IVolumeUpdater() = default;
	virtual std::shared_ptr<IVolumeDataDependency>  Update(double volumeThrshold, misVolumeViewingTypes volumeType, std::shared_ptr<IImage> currentImage) = 0;
	virtual void ClearVolumeThreshold() = 0;
};