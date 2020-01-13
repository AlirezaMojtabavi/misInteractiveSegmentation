#pragma once
#include "IAddFixedLandmarks.h"
MOCK_BASE_CLASS(MockAddFixedLandmarks, IAddFixedLandmarks)
{
	MOCK_NON_CONST_METHOD(AddLandmarks, 1, void(misLandmarkListTypdef ));
};
