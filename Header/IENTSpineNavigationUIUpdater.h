#pragma once

#include "misAutoCaptureScreenStrcts.h"
#include "misGuiStructures.h"
#include "misTrackingStateReport.h"

// The IDentalNavigationUpdater schedule updating navigation UI task by each pulse received 
class IENTSpineNavigationUIUpdater
{
public:
	virtual void SetFreezState(bool val) = 0;
	virtual void UpdateStatus() = 0;
	virtual ~IENTSpineNavigationUIUpdater() { }
};