#pragma once
#include "I3DModelTypeSelector.h"
#include "IVolumeDataDependency.h"
#include "misVolumeViewingTypes.h"

class IVolumeFactory
{
public:
	virtual ~IVolumeFactory() = default;
	virtual std::shared_ptr<IVolumeDataDependency> CreateTemporaryVolumeDependency(double volumeThreshold,
		std::shared_ptr<IImage> image,
		misVolumeViewingTypes volumeViewingType) = 0;
	virtual std::shared_ptr<IVolumeDataDependency> 	CreateTemporaryVolumeDependency(double volumeThreshold,
		std::shared_ptr<IImage> image, misApplicationType appType)  = 0 ;
	virtual misVolumeViewingTypes GetDefultVolumeViewingType(misImageDataModality modality, misApplicationType appType) = 0;

};
