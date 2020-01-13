#pragma once

#include "IDentalNavigationUiUpdater.h"


MOCK_BASE_CLASS(MockDentalNavigationUIUpdater, IDentalNavigationUiUpdater)
{
	MOCK_NON_CONST_METHOD(SetFreezState, 1, void(bool val));
	MOCK_NON_CONST_METHOD(UpdateStatus, 0, void());
	MOCK_NON_CONST_METHOD(UpdateCurrentPackage, 2, void(const misUID currentPackageUid,const misUID imageUid));

};
