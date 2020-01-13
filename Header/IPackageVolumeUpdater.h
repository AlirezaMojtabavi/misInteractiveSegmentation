#pragma once
#include "IImage.h"
#include "misobjectProperitiesEnums.h"
#include "ISimpleDataPackage.h"
#include "misVolumeViewingTypes.h"


class IPackageVolumeUpdater
{
	public:
		virtual void CreateTemporaryVolumeDependency(double volumeThreshold,
			std::shared_ptr <ISimpleDataPackage > package, std::shared_ptr<IImage> image, misVolumeViewingTypes volumeViewingType) = 0;
		virtual ~IPackageVolumeUpdater() = default;
};

