#pragma once

#include "IBiopsyNavigationUiUpdater.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockBiopsyNavigationUiUpdater, IBiopsyNavigationUiUpdater)
	{
		MOCK_NON_CONST_METHOD(PlanTargetIsPassed, 1, void(bool isInTargetRegion));
		MOCK_NON_CONST_METHOD(ForceViewersToFreez, 1, void(bool freezState), ForceViewersToFreez_sig1);
		MOCK_NON_CONST_METHOD(ForceViewersToFreez, 0, void(), ForceViewersToFreez_sig2);
		MOCK_NON_CONST_METHOD(UpdateCurrentPackage, 2, void(const std::string& currentSelectedObjectPackageUID, const std::string& imageUID));
		MOCK_NON_CONST_METHOD(UpdateStatus, 0, void());
		MOCK_NON_CONST_METHOD(SetStatusMessage, 1, void(misTrackingStateReport toolsStatus));
		MOCK_NON_CONST_METHOD(Update3DDistance, 0, void());
		MOCK_NON_CONST_METHOD(Update3DDistanceGUIState, 0, void());
		MOCK_NON_CONST_METHOD(UpdateNearesetLandmarkGUIState, 0, void());
		MOCK_NON_CONST_METHOD(UpdateTargetPointGUIState, 0, void());
		MOCK_NON_CONST_METHOD(ShowCutDirectionGrid, 1, void(bool cut));
		MOCK_NON_CONST_METHOD(UpdateTargetPointInfo, 1 , void(TargetPointData ));
		MOCK_NON_CONST_METHOD(UpdateNearesetLandmarkInfo, 0, void());
		MOCK_NON_CONST_METHOD(RaiseTrackingViewerEvent, 0, void());
		MOCK_NON_CONST_METHOD(SetAutoPilotButtonsEnable, 1, void(bool enable));
		MOCK_NON_CONST_METHOD(SetPlanTargetRadiusSlider, 1, void(double radius));
		MOCK_NON_CONST_METHOD(SelectPackage, 1, void(const std::string& uid));
		MOCK_NON_CONST_METHOD(UpdateViewTypes, 1, void(std::vector<std::string>));
		MOCK_NON_CONST_METHOD(ClearPackageListTreeView, 0, void());
		MOCK_NON_CONST_METHOD(DisableAllSliders, 0, void());
		MOCK_NON_CONST_METHOD(RaiseBackToPanStateEvent, 0, void());
		MOCK_NON_CONST_METHOD(RaiseTaskDoneOnSubTabLeaveEvent, 0, void());
		MOCK_NON_CONST_METHOD(UpdataCroppingDirectionInGUI, 1, void(misCroppingDirectionInVR coppingDirection));
		MOCK_NON_CONST_METHOD(UpdateGuiMessageBoard, 2, void(const std::string& message, IUserMessageBoardManager::MessageSeverity severity));
		MOCK_NON_CONST_METHOD(SetVirtualTipLengthText, 1, void(const double& length));
		MOCK_NON_CONST_METHOD(ShowPackageListInGUI, 0, void());
		MOCK_NON_CONST_METHOD(ShowSelectedPackage, 1,  void (const std::string& ));
		MOCK_NON_CONST_METHOD(UpdateZoomPercentage, 2, void(int, double));
		MOCK_NON_CONST_METHOD(UpdateCroppingDirectionInGUI, 1, void(misCroppingDirectionInVR));
		MOCK_NON_CONST_METHOD(UpdateLayout, 1, void (const misWindowsLayout&) );
		MOCK_NON_CONST_METHOD(ClearLayout, 0, void () );
	};

}