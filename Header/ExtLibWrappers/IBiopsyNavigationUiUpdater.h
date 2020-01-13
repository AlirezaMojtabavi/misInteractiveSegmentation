#pragma once
#include "misTrackingStateReport.h"
#include "misGuiStructures.h"
#include <voreen/misCroppingDirectionInVR.h>
#include "IUserMessageBoardManager.h"
#include "TargetPointData.h"
#include "InavigationUIUpdater.h"
#include "INavigationLayoutUiUpdater.h"

namespace parcast
{

	class IBiopsyNavigationUiUpdater : public INavigationUIUpdater, public INavigationLayoutUiUpdater
	{
	public:
		virtual ~IBiopsyNavigationUiUpdater() = default;

		virtual void PlanTargetIsPassed(bool isInTargetRegion) = 0;
		virtual void ForceViewersToFreez(bool freezState) = 0;
		virtual void ForceViewersToFreez() = 0;
		virtual void UpdateCurrentPackage(const std::string& currentSelectedObjectPackageUID, const std::string& imageUID) = 0;
		virtual void UpdateStatus() = 0;
		virtual void SetStatusMessage(misTrackingStateReport toolsStatus) = 0;
		virtual void Update3DDistance() = 0;
		virtual void Update3DDistanceGUIState() = 0;
		virtual void UpdateNearesetLandmarkGUIState() = 0;
		virtual void UpdateTargetPointGUIState() = 0;
		virtual void ShowCutDirectionGrid(bool cut) = 0;
		virtual void UpdateTargetPointInfo(TargetPointData distance) = 0;
		virtual void UpdateNearesetLandmarkInfo() = 0;
		virtual void RaiseTrackingViewerEvent() = 0;
		virtual void SetAutoPilotButtonsEnable(bool enable) = 0;
		virtual void SetPlanTargetRadiusSlider(double radius) = 0;
		virtual void DisableAllSliders() = 0;
		virtual void RaiseBackToPanStateEvent() = 0;
		virtual void RaiseTaskDoneOnSubTabLeaveEvent() = 0;
		virtual void UpdataCroppingDirectionInGUI(misCroppingDirectionInVR coppingDirection) = 0;
		virtual void UpdateGuiMessageBoard(const std::string& message, IUserMessageBoardManager::MessageSeverity severity) = 0;
		virtual void SetVirtualTipLengthText(const double& length) = 0;
	};

}
