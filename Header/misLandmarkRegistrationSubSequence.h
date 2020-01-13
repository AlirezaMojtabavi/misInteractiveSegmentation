#pragma once
#include "misMultiViewSubSequence.h"

#include "misToolFixationAnalysis.h"
#include "IUserMessageBoardManager.h"
#include "..\misRegistrationProdecure\misReportRegistrationResults.h"
#include "misObjectRangeStr.h"
#include "mislandMarkPosAndStatusStr.h"
#include "misPackageViewingItemsStrct.h"
#include "ToolRendererManager.h"
#include "misRegistrationStrcts.h"
#include "IViewingTypeColormapSelector.h"
#include "IImageToPatientLandmarkBasedRegistation.h"
#include "ILandmarkRegistrationUIAdapter.h"
#include "ICreateCorrelatedPackageList.h"
#include "IUpdateRegistrationViewWithLandMark.h"
#include "misDataSetManager.h"
#include "RegistrationCaptureLastPosition.h"
#include "IRegistrationCapturePoint.h"

class ICoordinateSystemRenderer;
class ITrackingTool;
class misDatasetManager;
class misImageToPatientLandmarkBasedRegistation;
class misGUIEvent;
class misTrackingStateReport;
class ITrackingTooolVisibiltyReport;
class IRegistrationErrorVisualizer;
class ITrackingToolQuery;
class IImage;

namespace parcast { class IInitialRegistrationResultApplier; }

class misLandmarkRegistrationSubSequence : public misMultiViewSubSequence
{
	friend class misRegistrationManager;

public:
	typedef std::set<std::shared_ptr<ITrackingTool>> ToolListType;

	misLandmarkRegistrationSubSequence(std::shared_ptr<INavigationViewersNView> groupViewer, 
			std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,

		std::shared_ptr<ILandmarkRegistrationUIAdapter>, 
		std::shared_ptr<IImageToPatientLandmarkBasedRegistation> 		imageToPatientLandmarkBasedRegistation, 
		std::shared_ptr<IViewingTypeColormapSelector> viewingTypeColormapSelector, std::shared_ptr<misSoftwareInformation> softwareInformation);
	void ResetLandmarkRegistrationSubSeq();
	void CaptureLastToolPositionAsLandmark();
	void RealseAllResources() override;
	void TaskOnLeave() override;
	void OnSelected() override;
	void UpdateSettingFromAppSetting() override;
	void UpdateStatus(long long int puls) override;
	void Render() override;
	bool ProcessRequest(misGUIEvent* pEvent) override;
	misEventListTypedef GetEventToGui() override;
	void ResetSetting() override;
	void SetTrackingState(CurrentSubSequenseStateStrct trackingState);
	void SetCurrentPackage(std::shared_ptr<ISimpleDataPackage> package);
	void AddTrackerTool(std::shared_ptr<ITrackingTool> tool);
	void AddRenderingTool(std::shared_ptr<ICoordinateSystemRenderer> renderingTool);
	void SetTooldata(ToolListType  val);
	void ResetTools();
	void UpadetTREBasedOnSurfaceRegistration();
	void UpdateRegistrationState();
	void SelectPoint(int index);
	void UpdateAutomaticCaptureLandmarkSetting(const misToolFixationPropertiesStr& settingForAutomaticCaptureLandmark);
	void SetImage(std::shared_ptr<IImage> val);
	void RequestTrackerConnection();
	void ResetTrackingEffects();
	void UpdatePreviousRegistrationResult();
	void SetPackage(std::shared_ptr<ISimpleDataPackage> val);
	void ShowCurrentPackage();
	bool TrackerIsConnected() const;
	std::string	GetCurrentPackagUsed() const;
	ToolListType GetTooldata() const;
	std::shared_ptr<IImageToPatientLandmarkBasedRegistation> GetLandmarkList() const;
	std::shared_ptr<ISimpleDataPackage> GetPackage() const;
	std::shared_ptr<ITrackingTooolVisibiltyReport> GetVisibiltyReporter();
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;

	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;


private:

	struct misThreadContainer
	{
		std::shared_ptr<IImage> m_image;
		misLandmarkRegistrationSubSequence* m_Instance;
	};

	const std::string m_ReportFileName;
	double GetTimeSinceToolLastCalibrated();
	
	void UpdateCameraPosition(double* focal) const;
	void ReturnToStartRegistrationState();
	void AutoUpdateNextPoint();
	void ForcedUpdateNextPoint(bool skipOnUncaptured);
	void CheckAutomaticCaptureLandmark();
	void ResetAutomaticCaptureLandmark();
	void UpdateViewWithMaxError();
	void UpdateTREError();
	void UpdateCurrentContext();
	void UpdateToolStatus();
	void UpdateLandmarkViewOnRestart();
	void UpdateCapturingProgressBarInGUI(double val);
	void UpdateSoundAlertStatus();
	void ResetToolStatus();
	void UpdateLandmarkSelectionStatusBasedOnRegistrationResult();
	void RequestToolRecalibration(std::string toolName);
	bool ShowRegisterationError();
	bool UpdateViewAndGUIWithLandmarkID(int landmarkIndex);
	bool PointIsValid(double* point);
	bool DistanceFromLandmarksIsValid(int currentSelectedLandmark);
	RegistrationResult AcceptRegistration();
	RegistrationResult UpdateSceneAfterRegistration();
	TREStrct CalculateTRE(double currentToolPosition[3]);
	// Examines visibility of tools with the specified application flag, and if such a tool is found that has been recently 
	// visible but is now invisible, creates the appropriate tool marker visibility status report event to be sent to GUI.
	// It returns true if the event was sent and false if sending of event for the specified application flag has not been needed.
	bool SendAppropriateToolMarkerVisibilityEvent();
	void RequestNavigationToolCalibration();
	// Logger routine for saving registration results
	void LogRegisatrationResults();
	// Updates the GUI based message board with the specified message and priority. I sends an event to the GUI. This method 
	// is bound and passed to the message board manager which will use it to display messages in turn.
	void UpdateGuiMessageBoard(const std::string& message, IUserMessageBoardManager::MessageSeverity severity);
	void SetStatusMessage(misTrackingStateReport toolsStatus);
	double GetCurrentThreshold(std::shared_ptr<IImage> pmisImage);
	template <class EventType, typename PayloadType>
	void InvokeLoadedEvent(const PayloadType& payload);
	template <class EventType>
	void InvokeUnloadedEvent();

public:
	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;
private:
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<ITrackingTool> m_TempraryTool;
	std::shared_ptr<ITrackingToolQuery> m_TrackingToolQuery;
	std::shared_ptr<parcast::IInitialRegistrationResultApplier> m_InitialRegistrationResultApplier;
	std::shared_ptr<ITrackingTooolVisibiltyReport> m_VisibiltyReporter;
	std::shared_ptr<IRegistrationErrorVisualizer> m_ErrorVisulizer;
	std::shared_ptr<IImage> m_Image;
	std::shared_ptr<IUserMessageBoardManager> m_MessageBoardManager;
	IUserMessageBoardManager::MessageId m_RegResultMsgId;
	IUserMessageBoardManager::MessageId m_LastPointErrorMsgId;
	IUserMessageBoardManager::MessageId m_NavigationToolVisibilityMsgId;
	IUserMessageBoardManager::MessageId m_ReferenceToolVisibilityMsgId;
	IUserMessageBoardManager::MessageId m_InterferenceMsgId;
	misReportRegistrationResults m_RegisrationReport;
	double m_LastAutoCaptureLandmarkValue;
	int m_CurrentSelectedLandmarkIndex;
	std::string m_ReferenceToolUID;
	Command* m_pObserver;
	ToolListType m_TrackerList;
	misDatasetManager* m_pDataManger;
	CurrentSubSequenseStateStrct m_TrackingState;
	// Note: create on landmark list in registration manger and pass it to all subsequence only misRegistrationManager is 
	// responsible for deleting it
	std::shared_ptr<IImageToPatientLandmarkBasedRegistation> m_ImageToReferenceRegistration;
	std::shared_ptr<misToolFixationAnalysis> m_AutomaticCapturelandmark = std::make_shared<misToolFixationAnalysis>();
	// a flag which is used to wait for a few minutes before starting to get landmarks
	bool m_WaitForAfewSeconds;
	bool m_TrackingEnabled;
	bool m_LandmarkRegistrationStatus;
	bool m_LastSoundAlertStatus;
	bool m_IsReferenceSet;
	bool m_CheckNewLandmarkMaxErrorForAccepting;
	bool m_SkipNonCapturedLandmarkAutomatocally;
	bool m_PlayAutoCapturingSound;
	bool m_PlayMeanError;
	bool m_LastVirtualKeyShowingStatus;
	bool m_TimerStarted;
	// flag that will be set if the last landmark must be selected 
	bool m_LastMustBeSelected = false;
	// Flag for show "This landmark caused to increase mean error!" Message.
	bool m_LastPointErrorMessage;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<parcast::ToolRendererManager> m_ToolRenderersManager = std::make_shared<parcast::ToolRendererManager>();
	std::shared_ptr<IViewingTypeColormapSelector> m_ViewingTypeColormapSelector;
	std::shared_ptr<ILandmarkRegistrationUIAdapter> m_LandamrRegUIAdapter;
	std::unique_ptr<ICreateCorrelatedPackageList> m_CreateCorrelatedPackageList;
	std::unique_ptr<IUpdateRegistrationViewWithLandMark> m_UpdateRegistrationViewWithLandMark;
	std::unique_ptr<parcast::IRegistrationCapturePoint> m_RegistrationCapturePoint;
	std::shared_ptr<parcast::RegistrationCaptureLastPosition> m_RegistrationCaptureLastPosition;
};