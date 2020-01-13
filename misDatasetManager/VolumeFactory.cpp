#include "stdafx.h"
#include "..\Header\VolumeFactory.h"
#include "misVolumeDataDependensies.h"
#include <IImage.h>
#include <misVolumeData.h>

std::shared_ptr<IVolumeDataDependency> VolumeFactory::CreateTemporaryVolumeDependency(double volumeThreshold,
	std::shared_ptr<IImage> image, misVolumeViewingTypes volumeViewingType)
{

 		std::shared_ptr<IVolumeDataDependency>	volumeStructData =
			std::make_shared<misVolumeDataDependensies>();
		volumeStructData->SetAutomaticallyCreated(true);
		volumeStructData->SetImage(image);
		if (volumeStructData->GetVolume() == 0)
			volumeStructData->SetVolume(std::make_shared<misVolumeData>());
		volumeStructData->GetVolume()->SetMinThreshold(volumeViewingType, volumeThreshold);
		volumeStructData->GetVolume()->SetComponentVisibilityAll();
		volumeStructData->GetVolume()->SetImageModality(image->GetImageModality());
		volumeStructData->SetParentImageUID(image->GetUID());
		auto  objectUid = volumeStructData->GetVolume()->GetObjectUID(volumeViewingType);
		mis3DModelObjectOpacityPropertiesStrct newvisibilityStrct;
		newvisibilityStrct.visibilityIn2DScene = false;
		volumeStructData->SetVisibilityIn2D(false);
		newvisibilityStrct.SetOpacityIn2DScene(0);
		volumeStructData->ClearObjectVisibilities();
		volumeStructData->SetObjectVisibilityProperties(objectUid, newvisibilityStrct);
		return volumeStructData;
 }

std::shared_ptr<IVolumeDataDependency> VolumeFactory::CreateTemporaryVolumeDependency(double volumeThreshold,
                                                                                        std::shared_ptr<IImage> image,
                                                                                        misApplicationType appType)
{
	auto volumeViewingType = GetDefultVolumeViewingType(image->GetImageModality(), appType);
	return CreateTemporaryVolumeDependency(volumeThreshold, image, volumeViewingType);
}

misVolumeViewingTypes VolumeFactory::GetDefultVolumeViewingType(misImageDataModality modality,
                                                                misApplicationType appType)
{
	ModalityToViewingtypeConverter convertor(modality, appType);
	return convertor.GetDefultVolumeViewingType();
}
