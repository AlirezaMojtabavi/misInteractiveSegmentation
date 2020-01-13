#pragma once
#include "IPackageVolumeUpdater.h"

class misPackageVolumeUpdater :
	public IPackageVolumeUpdater
{
public:
 
	        

	// Inherited via IPackageVolumeUpdater
	virtual void CreateTemporaryVolumeDependency(double volumeThreshold, std::shared_ptr<ISimpleDataPackage> package, std::shared_ptr<IImage> image, misVolumeViewingTypes volumeViewingType) override;

};
