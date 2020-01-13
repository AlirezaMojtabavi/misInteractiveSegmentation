#pragma once

#include "misMultiViewSubSequence.h"

#include "..\misRegistrationProdecure\misReportRegistrationResults.h"
#include "IUserMessageBoardManager.h"
#include "misToolFixationAnalysis.h"
#include "ToolRendererManager.h"
#include "misRegistrationEnums.h"
#include "IViewingTypeColormapSelector.h"
#include "IImageToPatientLandmarkBasedRegistation.h"
#include "misImageToPatientLandmarkBasedRegistation.h"

template<class TCoordRep = double>
class mis3DPoint;

class ITrackingTool;
class misToolLocator;
class cln_MemoryTestApplication;
class misDatasetManager;
class IImage;
class misLandmarkPointerRepresentation;
class misGuiEvent;
class ICoordinateSystemRenderer;
class misTrackingStateReport;
class ITrackingToolQuery;
class ITrackingTooolVisibiltyReport;
struct mislandMarkPosAndStatusStr;

struct TREStrct;

namespace parcast { class IInitialRegistrationResultApplier; }

class  misDentaLandmarkRegistrationSubSequence : public misMultiViewSubSequence
{
	friend class misRegistrationSequence;

public:
	misDentaLandmarkRegistrationSubSequence(std::shared_ptr<INavigationViewersNView> groupViewer,
		misApplicationType applicationType);
	typedef std::set<std::shared_ptr<ITrackingTool>> ToolListType;
	typedef itk::Vector<double> itkVectorType;

	void SetLandmarkList(std::shared_ptr<IImageToPatientLandmarkBasedRegistation> val);
	void SetTrackingState(CurrentSubSequenseStateStrct trackingState);
	void SetCurrentPackagUsed(std::shared_ptr<IViewingTypeColormapSelector> viewingTypeColormapSelector, std::string val);
	void SetViewr(std::shared_ptr<INavigationViewersNView>  val);
	void AddTrackerTool(std::shared_ptr<ITrackingTool>   tool);
	void AddRenderingTool(std::shared_ptr<ICoordinateSystemRenderer> renderingTool);
	void SetTooldata(ToolListType val);
	void ShowTools(bool value);
	void ResetTools();
	void RealseAllResources();
	void TaskOnLeave();
	void UpdateViewWithLandMark(int index);
	void OnSelected();
	void UpdateSettingFromAppSetting();
	void UpadetTREBasedOnSurfaceRegistration();
	void UpdateStatus(long long int puls);
	void UpdateRegistrationState();
	void Render();
	void SetImage(std::shared_ptr<IImage> val);
	void UpdatePreviousRegistrationResult();
	void CheckTrackerState();
	void ResetSetting();
	void SetTemporaryPackage(std::shared_ptr<ISimpleDataPackage> val);
	

	bool ProcessRequest(misGUIEvent* pEvent);
	std::string	GetCurrentPackagUsed() const;
	ToolListType GetTooldata() const;
	std::shared_ptr<IImageToPatientLandmarkBasedRegistation> GetLandmarkList() const;
	misEventListTypedef GetEventToGui();
	CurrentSubSequenseStateStrct GetTrackingState() const;
	std::shared_ptr<ISimpleDataPackage> GetTemporaryPackage() const;
	std::shared_ptr<ITrackingTooolVisibiltyReport> GetVisibiltyReporter();

	void CaptureLastToolPositionAsLandmark();
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;

private:

	const std::string m_ReportFileName = "RegistrationReport.txt";

	void UpdateLandRegState();
	void UpdateCameraPosition(double* focal);
	void ResetTrackingEffects();
	void ResetLandmarkRegistration();
	void AutoUpdateNextPoint();
	void ForcedUpdateNextPoint(bool skipOnUncaptured);
	void UpdateLandmarkErrorListInGUI(std::vector<mislandMarkPosAndStatusStr> landmarks);
	void CheckAutomaticCaptureLandmark();
	void ResetAutomaticCaptureLandmark();
	void UpdateViewWithMaxError();
	void UpdateTreError();
	void UpdateGUI();
	void UpdateToolStatus();
	void UpdateLandmarkViewOnRestart();
	void UpdateCapturingProgressBarInGUI(double val);
	void UpdateSoundAlertStatus();
	void RemoveRegistrationErrorLandmarks();
	void SetRegistrationErrorLandmark(double mainPosition[3], double finalRegisteredPosition[3]);
	void Update3DViewerCP(double * finalRegisteredPosition, double * mainPosition);
	void Update2DViewerCP(double * mainPosition, double * finalRegisteredPosition);
	void Reset2DViewersZoom();
	void UpdateCPPosition(std::shared_ptr<misLandmarkPointerRepresentation> cpPoint,
		mis3DPoint<double> finalRegisteredPosition, itkVectorType labelPosition,
		mis3DPoint<double> &endPointOfProjectedArrow);
	void ResetToolStatus();
	void CreateTemporaryVolumeDependency(double volumeThreshold, misVolumeViewingTypes currentType);
	void UpdateLandmarkSelectionStatusBasedOnRegistrationResult();
	void RequestToolRecalibration(std::string toolName);
	void GetLastCapturedPosition(ICoordinateSystem* refernecCorinate, double outputPosition[3]);
	void RequestNavigationToolCalibration();
	void LogRegisatrationResults();
	void UpdateGuiMessageBoard(const std::string& message, IUserMessageBoardManager::MessageSeverity severity);
	void SetStatusMessage(misTrackingStateReport toolsStatus);
	bool SendAppropriateToolMarkerVisibilityEvent();
	bool UpdateVolume3D();
	bool ShowRegisterationError();
	bool UpdateViewAndGUIWithLandmarkID(int landmarkIndex);
	bool PointIsValid(double* point);
	bool DistanceFromLandmarksIsValid(int currentSelectedLandmark);
	double GetTimeSinceToolLastCalibrated();
	std::shared_ptr<misLandmarkPointerRepresentation> CreateCPPoint();
	RegistrationResult AcceptRegistration();
	RegistrationResult UpdateSceneAfterRegistration();
	TREStrct CalculateTRE(double  currentToolPosition[3]);
	misVolumeViewingTypes UpdateCurrentVolumeType();

private:
	bool m_WaitForAfewSeconds = false;
	bool m_LandmarkRegistrationStatus{};
	bool m_LastSoundAlertStatus{};
	bool m_IsReferenceSet = false;
	bool m_CheckNewLandmarkMaxErrorForAccepting{};
	bool m_SkipNonCapturedLandmarkAutomatocally{};
	bool m_PlayAutoCapturingSound{};
	bool m_PlayMeanError{};
	bool m_LastVirtualKeyShowingStatus{};
	bool m_TimerStarted{};
	bool m_LastMustBeSelected = true;
	bool m_LastPointErrorMessage{};
	bool m_TrackingEnabled;
	double m_LastAutoCaptureLandmarkValue{};
	int m_CurrentSelectedLandmarkIndex{};

	std::shared_ptr<ISimpleDataPackage> m_TemporaryPackage = nullptr;
	std::shared_ptr<ITrackingTool> m_TempraryTool;
	std::shared_ptr<ITrackingToolQuery> m_TrackingToolQuery;
	std::shared_ptr<IImage> m_Image;
	std::shared_ptr<IUserMessageBoardManager> m_MessageBoardManager;
	std::shared_ptr<ITrackingTooolVisibiltyReport> m_VisibiltyReporter;
	std::shared_ptr<parcast::IInitialRegistrationResultApplier> m_InitialRegistrationResultApplier;
	std::vector<std::shared_ptr<misLandmarkPointerRepresentation>> m_CorrectionVectorRepList2D;
	std::vector<std::shared_ptr<misLandmarkPointerRepresentation>> m_CorrectionVectorRepList3D;
	std::string m_ReferenceToolUID;
	std::string m_CurrentPackagUsed;
	Command* m_pObserver{};
	misDatasetManager* m_pDataManger;

	IUserMessageBoardManager::MessageId m_RegResultMsgId = 0;
	IUserMessageBoardManager::MessageId m_LastPointErrorMsgId = 0;
	IUserMessageBoardManager::MessageId m_NavigationToolVisibilityMsgId = 0;
	IUserMessageBoardManager::MessageId m_ReferenceToolVisibilityMsgId = 0;
	IUserMessageBoardManager::MessageId m_InterferenceMsgId = 0;

	ToolListType m_TrackerList;
	CurrentSubSequenseStateStrct m_TrackingState;
	std::shared_ptr<IImageToPatientLandmarkBasedRegistation> m_ImageToReferenceRegistration;
	misToolFixationAnalysis m_AutomaticCapturelandmark;
	misVolumeViewingTypes m_LastVolumeType;
	misReportRegistrationResults m_RegisrationReport;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<parcast::ToolRendererManager> m_ToolRenderersManager = std::make_shared<parcast::ToolRendererManager>();
	std::shared_ptr<IViewingTypeColormapSelector> m_ViewingTypeColormapSelector;
};