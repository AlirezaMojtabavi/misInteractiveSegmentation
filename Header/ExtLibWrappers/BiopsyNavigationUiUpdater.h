#pragma once
#include "IBiopsyNavigationUiUpdater.h"
#include "IGeneralNavigationHelper.h"
#include "INavigationTrackingHelper.h"
#include "INavigationLayoutUiUpdater.h"

namespace parcast
{

	class BiopsyNavigationUiUpdater : public IBiopsyNavigationUiUpdater, public INavigationLayoutUiUpdater
	{
	public:
		explicit BiopsyNavigationUiUpdater(
			const std::string& sequenceName,
			const std::string& subSequenceName,
			std::shared_ptr<IGeneralNavigationHelper> navHelper,
			std::shared_ptr<INavigationTrackingHelper> trackingHelper,
			itk::Object::Pointer eventForwarder);

		void PlanTargetIsPassed(bool isInTargetRegion) override;
		void ForceViewersToFreez(bool freezState) override;
		void ForceViewersToFreez() override;
		void UpdateCurrentPackage(const std::string& currentSelectedObjectPackageUID, const std::string& imageUID) override;
		void UpdateStatus() override;
		virtual void ShowPackageListInGUI() override;
		virtual void ShowSelectedPackage(const std::string& uid) override;
		void SetStatusMessage(misTrackingStateReport toolsStatus) override;
		void Update3DDistance() override;
		void Update3DDistanceGUIState() override;
		void UpdateNearesetLandmarkGUIState() override;
		void UpdateTargetPointGUIState() override;
		void ShowCutDirectionGrid(bool cut) override;
		void UpdateTargetPointInfo(TargetPointData distance) override;
		void UpdateNearesetLandmarkInfo() override;
		void RaiseTrackingViewerEvent() override;
		void SetAutoPilotButtonsEnable(bool enable) override;
		void SetPlanTargetRadiusSlider(double radius) override;
		void UpdateViewTypes(std::vector<std::string> layouts) override;
		void ClearPackageListTreeView() override;
		void DisableAllSliders() override;
		void RaiseBackToPanStateEvent() override;
		void RaiseTaskDoneOnSubTabLeaveEvent() override;
		void UpdataCroppingDirectionInGUI(misCroppingDirectionInVR coppingDirection) override;
		void UpdateGuiMessageBoard(const std::string& message, IUserMessageBoardManager::MessageSeverity severity) override;
		void UpdateLayout(const misWindowsLayout& setting) override;
		void ClearLayout() override;
		void SetVirtualTipLengthText(const double& length) override;
		void UpdateZoomPercentage(int percentage, double proportion) override;
		void UpdateCroppingDirectionInGUI(misCroppingDirectionInVR cropping) override;

	private:

		template <class EventType, typename PayloadType>
		void InvokeParentLoadedEvent(const PayloadType& payload)
		{
			EventType ev;
			ev.Set(payload);
			ev.SetSequenceName(m_SequenceName);
			ev.SetSubTab(m_SubsequenceName);
			m_ParentEventHandler->InvokeEvent(ev);
		}

		template <class EventType>
		void InvokeParentUnloadedEvent()
		{
			EventType ev;
			ev.SetSequenceName(m_SequenceName);
			ev.SetSubTab(m_SubsequenceName);
			m_ParentEventHandler->InvokeEvent(ev);
		}

		void UpdateAutomaticGotoFullScreenWindow();
		void UpdateSnapShotTakerOnToolFixation();
		void UpdateVectorToTargetPoint();
		void UpdateNearestLandmarkInformation();
		void UpdateToolsReport();
		void UpdateMeasurmentState();
		void UpdateCaptureScreenStatus();
		bool SendAppropriateToolMarkerVisibilityEvent();

		std::shared_ptr<IGeneralNavigationHelper> m_GeneralNavigationHelper;
		std::shared_ptr<INavigationTrackingHelper> m_TrackingHelper;
		std::shared_ptr<IUserMessageBoardManager> m_MessageBoardManager;

		misCaptureScreenStatus m_CaptureStatus = unsetCaptureScreen;
		itk::Object::Pointer m_ParentEventHandler;

		IUserMessageBoardManager::MessageId m_NavigationToolVisibilityMsgId;
		IUserMessageBoardManager::MessageId m_ReferenceToolVisibilityMsgId;
		IUserMessageBoardManager::MessageId m_InterferenceMsgId;
		IUserMessageBoardManager::MessageId m_PackageSelectedMsgId;

		std::string m_SequenceName;
		std::string m_SubsequenceName;
		double m_AutomaticGotoFullScreenWindowValue = 0;
		double m_SnapshotTakerActionValue = 0;
		parcast::VectorD3 m_LastVectorToTargetPoint;
		bool m_FreezState = false;
	};

}
