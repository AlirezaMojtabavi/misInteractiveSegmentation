#pragma once
#include "IVolumeFactory.h"
#include "ModalityToViewingtypeConverter.h"
#include "misVolumeViewingTypes.h"

class VolumeFactory :	public IVolumeFactory
{
public:

	std::shared_ptr<IVolumeDataDependency> CreateTemporaryVolumeDependency(double volumeThreshold,
		std::shared_ptr<IImage> image, misVolumeViewingTypes volumeViewingType) override;
	std::shared_ptr<IVolumeDataDependency> 	CreateTemporaryVolumeDependency(double volumeThreshold,
	                                std::shared_ptr<IImage> image, misApplicationType appType) override;
	misVolumeViewingTypes GetDefultVolumeViewingType(misImageDataModality modality, misApplicationType appType) override;
};

