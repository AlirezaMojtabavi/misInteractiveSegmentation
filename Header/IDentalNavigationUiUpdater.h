#pragma once
#include  "misTypes.h"
// The IDentalNavigationUpdater schedule updating navigation UI task by each pulse received 
class IDentalNavigationUiUpdater
{
public:
	virtual void SetFreezState(bool val) = 0;
	virtual void UpdateStatus() = 0;
	virtual void UpdateCurrentPackage(const misUID currentSelectedObjectPackageUid, const misUID imageUID) = 0;
	virtual ~IDentalNavigationUiUpdater() { }
};