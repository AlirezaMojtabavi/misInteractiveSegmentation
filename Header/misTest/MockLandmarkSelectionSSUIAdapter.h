#pragma once
#include "ILandmarkSelectionSSUIAdapter.h"
MOCK_BASE_CLASS(MockLandmarkSelectionSSUIAdapter, ILandmarkSelectionSSUIAdapter)
{
	MOCK_NON_CONST_METHOD(UpdateThresholdSlider, 2, void(double , misObjectRangeStr ) );
	MOCK_NON_CONST_METHOD(SaveSoloution, 0,void () );
	MOCK_NON_CONST_METHOD(BackToPanStateEventCore, 0, void() );
	MOCK_NON_CONST_METHOD(SendVolumeTypeEvent, 1, void(misVolumeViewingTypes));
	MOCK_NON_CONST_METHOD(SendImageModalityEvent, 1, void(misImageDataModality modality) );
	MOCK_NON_CONST_METHOD(RegistrationLandmarkSelectionIDChanged, 1, void (unsigned int landmarkIndex) );
};
