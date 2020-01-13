#pragma once
#include "misTypes.h"
#include "INavigationLayoutUiUpdater.h"
#include "misTrackingStateReport.h"
#include <misEnums.h>
#include "InavigationUIUpdater.h"

enum misCroppingDirectionInVR;

// The IDentalNavigationUpdater schedule updating navigation UI task by each pulse received 
class IENTNavigationUIUpdater :public INavigationLayoutUiUpdater, public INavigationUIUpdater
{
public:
	virtual void SetFreezState(bool val) = 0;
	virtual void UpdateStatus() = 0;
	virtual void UpdateCurrentPackage(misUID currentSelectedObjectPackageUID, misUID imageUID) = 0;
	virtual void UpdateObliqueMode(const bool isObliqueView, const misCroppingDirectionInVR croppingDirection) = 0;

	virtual void SetStatusMessage(misTrackingStateReport toolsStatus) = 0;
	virtual void SetVirtualTipLengthText(const double& length) = 0;
	virtual void PlanTargetIsPassed(bool isInTargetRegion) = 0;

	virtual ~IENTNavigationUIUpdater() { }
};