#pragma once
#include "IlandamrkSelectionSyncronizeLandamrks.h"
MOCK_BASE_CLASS(MocklandamrkSelectionSyncronizeLandamrks, IlandamrkSelectionSyncronizeLandamrks)
{
	MOCK_NON_CONST_METHOD(SyncroizeLandmarks, 2, void (std::shared_ptr<IImageToPatientLandmarkBasedRegistation>,
		std::shared_ptr<ISimpleDataPackage> ) );
};
