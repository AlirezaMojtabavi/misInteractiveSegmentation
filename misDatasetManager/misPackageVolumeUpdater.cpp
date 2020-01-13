#include "stdafx.h"
#include "misPackageVolumeUpdater.h"
#include "VolumeFactory.h"

void misPackageVolumeUpdater::CreateTemporaryVolumeDependency(
    double volumeThreshold, std::shared_ptr<ISimpleDataPackage> package,
    std::shared_ptr<IImage> image, misVolumeViewingTypes volumeViewingType)
{
	auto volumeFactory = std::make_unique<VolumeFactory>();
  const auto volumeDependency = volumeFactory->CreateTemporaryVolumeDependency(
      volumeThreshold, image, volumeViewingType);
  package->DeleteAllVolumedatas();
  package->AddNextVolumedata(volumeDependency);
}
