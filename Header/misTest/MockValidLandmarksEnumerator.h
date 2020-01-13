#pragma once
#include "IValidLandmarksEnumerator.h"
MOCK_BASE_CLASS(MockValidLandmarksEnumerator, IValidLandmarksEnumerator)
{
	MOCK_NON_CONST_METHOD(GetNumberofCurrentValidLandmarks, 0, size_t GetNumberofCurrentValidLandmarks());
};
