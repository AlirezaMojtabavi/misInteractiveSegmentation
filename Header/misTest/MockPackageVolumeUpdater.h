#pragma once
 
#include "IPackageVolumeUpdater.h"
MOCK_BASE_CLASS(MockPackageVolumeUpdater, IPackageVolumeUpdater)
{

	MOCK_NON_CONST_METHOD(CreateTemporaryVolumeDependency, 4, void(double , std::shared_ptr <ISimpleDataPackage >, std::shared_ptr<IImage> , misVolumeViewingTypes ));

 };
