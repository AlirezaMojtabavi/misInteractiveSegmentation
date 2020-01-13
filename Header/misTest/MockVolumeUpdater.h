#pragma once
#include "IVolumeUpdater.h"
MOCK_BASE_CLASS(MockVolumeUpdater, IVolumeUpdater)
{
	MOCK_NON_CONST_METHOD(Update, 3, std::shared_ptr<IVolumeDataDependency>(double, misVolumeViewingTypes, std::shared_ptr<IImage>));
	MOCK_NON_CONST_METHOD(ClearVolumeThreshold, 0, void());;
};