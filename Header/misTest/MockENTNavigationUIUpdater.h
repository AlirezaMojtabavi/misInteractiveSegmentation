#pragma once

#include "IENTNavigationUIUpdater.h"

MOCK_BASE_CLASS(MockENTNavigationUIUpdater, IENTNavigationUIUpdater)
{
	MOCK_NON_CONST_METHOD(SetFreezState, 1, void(bool val));
	MOCK_NON_CONST_METHOD(UpdateStatus, 0, void());
	MOCK_NON_CONST_METHOD(ShowPackageListInGUI, 1, void(misUID selectedPackge));
	MOCK_NON_CONST_METHOD(UpdateCurrentPackage, 2, void(misUID currentSelectedObjectPackageUID, misUID imageUID));
	MOCK_NON_CONST_METHOD(UpdateObliqueMode, 2, void(const bool isObliqueView, const misCroppingDirectionInVR croppingDirection));
	MOCK_NON_CONST_METHOD(ForceViewersToFreez, 1, void(bool freezState));
	MOCK_NON_CONST_METHOD(SetStatusMessage, 1, void(misTrackingStateReport toolsStatus));
	MOCK_NON_CONST_METHOD(SetVirtualTipLengthText, 1, void(const double& length));
	MOCK_NON_CONST_METHOD(UpdateLayout, 1, void(const misWindowsLayout&));
	MOCK_NON_CONST_METHOD(ClearLayout, 0, void());
	MOCK_NON_CONST_METHOD(PlanTargetIsPassed, 1, void(bool isInTargetRegion));

};

