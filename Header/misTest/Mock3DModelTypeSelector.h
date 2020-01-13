#pragma once
#pragma once
#include "I3DModelTypeSelector.h"



MOCK_BASE_CLASS(Mock3DModelTypeSelector, I3DModelTypeSelector)
{
	MOCK_CONST_METHOD(GetMOdelType, 2, mis3DModelTypes(misImageDataModality, misVolumeViewingTypes));
};
