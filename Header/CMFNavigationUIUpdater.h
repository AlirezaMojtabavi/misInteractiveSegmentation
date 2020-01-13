#pragma once

#include "misAutoCaptureScreenStrcts.h"
#include "IUserMessageBoardManager.h"
#include "ICMFNavigationUIUpdater.h"

class IUserMessageBoardManager;
class INavigationTrackingHelper;
class IGeneralNavigationHelper;
namespace parcast
{
	class CMFNavigationUIUpdater : public ICMFNavigationUIUpdater
	{
	public:
		CMFNavigationUIUpdater(const std::string& sequenceName, const std::string& subSequenceName,
			std::shared_ptr<IGeneralNavigationHelper> navHelper, std::shared_ptr<INavigationTrackingHelper> trackingHelper,
			itk::Object::Pointer eventForwarder);

		void UpdateStatus() override;
		void ShowSelectedPackage(const std::string& uid) override;
		void ShowPackageListInGUI() override;
		void UpdateObliqueMode(const bool isObliqueView, const misCroppingDirectionInVR croppingDirection) override;
		void SetFreezState(bool val) override;
		void UpdateCurrentPackage(misUID currentSelectedObjectPackageUID, misUID imageUID) override;
		void UpdateLayout(const misWindowsLayout&) override;
		void ClearLayout() override;
		void ForceViewersToFreez(bool freezState) override;
		void SetStatusMessage(misTrackingStateReport toolsStatus) override;
		void SetVirtualTipLengthText(const double& length) override;
		void PlanTargetIsPassed(bool isInTargetRegion) override;
		void UpdateViewTypes(std::vector<std::string> layouts) override;
		void ClearPackageListTreeView() override;

		void UpdateCroppingDirectionInGUI(misCroppingDirectionInVR cropping) override;
		void UpdateZoomPercentage(int percentage, double proportion) override;

	private:
		void UpdateAutomaticGotoFullScreenWindow();
		void UpdateNearestLandmarkInformation();
		void UpdateMeasurmentState();
		void UpdateCaptureScreenStatus();
		void UpdateVectorToTargetPoint();
		void UpdateToolsReport(void);
		void UpdateSnapShotTakerOnToolFixation(void);
		void UpdateGuiMessageBoard(const std::string& message, IUserMessageBoardManager::MessageSeverity severity);

		// Examines visibility of tools , and if such a tool is found that has been recently 
		// visible but is now invisible, creates the appropriate tool marker visibility status report event to be sent to GUI.
		// It returns true if the event was sent and false if sending of event for the specified application flag has not been needed.
		bool SendAppropriateToolMarkerVisibilityEvent();


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


	private:
		std::shared_ptr<IGeneralNavigationHelper> m_GeneralNavigationHelper;
		std::shared_ptr<INavigationTrackingHelper> m_TrackingHelper;
		itk::Object::Pointer m_ParentEventHandler;
		const std::string m_SequenceName;
		const std::string m_SubsequenceName;

		parcast::Vector<double> m_LastVectorToTargetPoint;
		bool m_FreezState;
		double m_AutomaticGotoFullScreenWindowValue;
		misCaptureScreenStatus m_CaptureStatus;
		double m_SnapshotTakerActionValue;
		std::shared_ptr<IUserMessageBoardManager> m_MessageBoardManager;
		IUserMessageBoardManager::MessageId m_NavigationToolVisibilityMsgId;
		IUserMessageBoardManager::MessageId m_ReferenceToolVisibilityMsgId;
		IUserMessageBoardManager::MessageId m_InterferenceMsgId;
		IUserMessageBoardManager::MessageId m_PackageSelectedMsgId;
	};
}
