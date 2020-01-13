#pragma once

#include "IVolumeFactory.h"

MOCK_BASE_CLASS(MockVolumeFactory, IVolumeFactory)
{
	MOCK_NON_CONST_METHOD(CreateTemporaryVolumeDependency, 3, std::shared_ptr<IVolumeDataDependency>(double ,
		std::shared_ptr<IImage> ,
		misVolumeViewingTypes volumeViewingType), CreateTemporaryVolumeDependency1);
	MOCK_NON_CONST_METHOD(CreateTemporaryVolumeDependency, 3, std::shared_ptr<IVolumeDataDependency>(double ,
		std::shared_ptr<IImage> , misApplicationType ), CreateTemporaryVolumeDependency2);
	MOCK_NON_CONST_METHOD(GetDefultVolumeViewingType, 2, misVolumeViewingTypes(misImageDataModality modality, misApplicationType appType));
};
