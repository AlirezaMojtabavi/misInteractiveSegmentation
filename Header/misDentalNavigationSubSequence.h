#pragma once

#include "misMultiViewSubSequence.h"

#include "IUserMessageBoardManager.h"
#include "misAutoCaptureScreenStrcts.h"
#include "ApproachAndModelInformationStrct.h"

#include "ITrackerImageSynchronizer.h"
#include "IPlanNavigationVisualizer.h"
#include "IPositionInPlanCoordinateSystemCalculatorSetter.h"
#include "IPilotIndicatorColorSpecifier.h"
#include "misWindow.h"

class IDentalNavigationUiUpdater;
class IPanoramicTransformConverter;
class IStatusLogger;
class ITrackingToolQuery;
class IGeneralNavigationHelper;
class IPackageDataVisualizer;
class INavigationPackageFinder;
class IFixedPointsDistanceMeasurment;
class ITargetDistanceMeasurement;
class ICheckPointsDistanceMeasurement;
class INavigationTrackingHelper;
class misTrackingStateReport;
class IPlanningNavigation;
class IDatasetManager;
class ISettingsContainer;
class misPlanData;

namespace parcast
{
	class IAutomaticCalibrationDetector;
	class CoordSysCorrelationVariationAdapter;
	class VisibilityManagement;
	class CoordSysCorrelationVariationAdapterUi;
}

using namespace parcast;

class misDentalNavigationSubSequence : public misMultiViewSubSequence
{
public:
	misDentalNavigationSubSequence(
		std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > cSCorrelationManager,
		std::shared_ptr<ISubsequenceLayout> uiModel,
		std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorSetter> positionInPlanCoordinateSystemCalculator,
		std::shared_ptr<IPlanNavigationVisualizer> planNavigationVisualizer,
		std::shared_ptr<IPilotIndicatorColorSpecifier> crossIndicatorColorSpecifier,
		std::shared_ptr<IPilotIndicatorColorSpecifier> circleIndicatorColorSpecifier,
		std::shared_ptr<IPilotIndicatorColorSpecifier> depthIndicatorColorSpecifier);
	misDentalNavigationSubSequence(std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > cSCorrelationManager,
		std::shared_ptr<IGeneralNavigationHelper> navHelper,
		IDatasetManager* datasetManager, std::shared_ptr<IPlanningNavigation> planNav,
		std::shared_ptr<IDentalNavigationUiUpdater> navUiUpdater, std::shared_ptr<INavigationTrackingHelper> trackingHelper,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer, std::shared_ptr<IUserMessageBoardManager> messageBoard,
		std::shared_ptr<IStatusLogger> toolCorrelationLogger,
		const std::string& sequenceName, const std::string& subsequenceName, std::shared_ptr<IGroupViewerSetting> groupVieweSetting, std::shared_ptr<ISubsequenceLayout> model,
		misApplicationType applicationType);

	virtual void AddPilot();
	void OnSelected();
	void UpdateSettingFromAppSetting();
	bool ProcessRequest(misGUIEvent* pEvent);
	void Render();
	virtual std::vector<std::shared_ptr<I3DViewer>> GetAllViewers();
	void TaskOnLeave();
	void UpdateStatus(long long int puls);
	void ResetSetting();
	void RealseAllResources();
	misEventListTypedef GetEventToGui();
	void SetCSCorrelationManager(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val) ;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;

private:
	void InitializeObject();
	std::shared_ptr<IAutomaticCalibrationDetector> GetAutomaticCalibrationDetector();

	// Examines visibility of tools , and if such a tool is found that has been recently 
	// visible but is now invisible, creates the appropriate tool marker visibility status report event to be sent to GUI.
	// It returns true if the event was sent and false if sending of event for the specified application flag has not been needed.
	bool SendAppropriateToolMarkerVisibilityEvent();

	void ShowTreeInformation();
	void UpdatePlanning();
	virtual void SetPackageContent();
	virtual void ShowCurrentPackageContentsInViewer();
	virtual void ShowPackageListInGUI();
	void Update3DModelSettingPanelPropertiesGUI();
	void UpdateImageSettingPanelPropertiesGUI();
	void UpdateZoomPercentage(int percentage, double proportion);
	void UpdataCroppingDirectionInGUI();
	void UpdateGuiMessageBoard(const std::string& message, IUserMessageBoardManager::MessageSeverity severity);
	void UpdateByTrackingStatus();
	void SetStatusMessage(misTrackingStateReport toolsStatus);
	std::shared_ptr<IStatusLogger> GetToolCorrelationLogger();	// Always check for null return.
	bool GuaranteeToolCorrelVarExists();    // Always check for null return.
	std::shared_ptr<ITrackingToolQuery> GetToolQuery();	// Always check for null return.
	int GetDefaultDejitterizerKernelLength(std::shared_ptr<const ISettingsContainer> appSettings);

	template <class EventType, typename PayloadType>
	void InvokeLoadedEvent(const PayloadType& payload);

	template <class EventType>
	void InvokeUnloadedEvent();

	std::shared_ptr<IGeneralNavigationHelper> m_GeneralNavigationHelper;
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<INavigationPackageFinder> m_PackageFinder;
	std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorSetter> m_PositionInPlanCoordinateSystemCalculator;
	std::shared_ptr<IPlanNavigationVisualizer> m_PlanNavigationVisualizer;
	std::shared_ptr<IPanoramicTransformConverter> m_PanoramicTransformConverter;
	std::shared_ptr<IPanoramicCoordinatesConverter> m_PanoramicCoordinatesConverter;
	std::shared_ptr<IUserMessageBoardManager> m_MessageBoardManager;
	std::shared_ptr<IFixedPointsDistanceMeasurment> m_FixedPointsDistanceMeasure;
	std::shared_ptr<ITargetDistanceMeasurement> m_DistanceToTarget;
	std::shared_ptr<ICheckPointsDistanceMeasurement> m_DistanceToCheckPoint;
	misCaptureScreenStatus m_CaptureStatus;
	IUserMessageBoardManager::MessageId m_NavigationToolVisibilityMsgId;
	IUserMessageBoardManager::MessageId m_ReferenceToolVisibilityMsgId;
	IUserMessageBoardManager::MessageId m_InterferenceMsgId;
	IUserMessageBoardManager::MessageId m_PackageSelectedMsgId;
	double m_AutomaticGotoFullScreenWindowValue;
	bool m_FreezState;
	double m_lastPointerDistanceToTargetPoint;
	double m_lastTakingSnapshotValue;
	IDatasetManager* m_DataSetManger;
	ApproachAndModelInformationStrct m_SelectedObjectInformation;
	std::shared_ptr<INavigationTrackingHelper> m_TrackingHelper;
	std::shared_ptr<IDentalNavigationUiUpdater> m_NavigationUiUpdater;
	std::weak_ptr<misPlanData> m_CurrentPlannedScrew;
	std::shared_ptr<IStatusLogger> m_ToolCorrelationLogger;	// Don't use except in GetToolCorrelationLogger
	std::shared_ptr<ITrackingToolQuery> m_ToolQuery;	// Don't use except in GetToolQuery
	std::shared_ptr<ITrackerImageSynchronizer> m_ToolSync;
	std::shared_ptr<ISubsequenceLayout> m_UiModel;
	std::shared_ptr<IAutomaticCalibrationDetector> m_AutomaticCalibrationDetector;
	std::shared_ptr<Iwindows> m_PilotWindow;
	std::unique_ptr<CoordSysCorrelationVariationAdapter> m_ToolCorrelVar;
	std::shared_ptr<VisibilityManagement> m_VisibilityManagement;
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::shared_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<misWindow> m_PilotWin;
	std::shared_ptr<IPilotIndicatorColorSpecifier> m_CrossIndicatorColorSpecifier;
	std::shared_ptr<IPilotIndicatorColorSpecifier> m_CircleIndicatorColorSpecifier;
	std::shared_ptr<IPilotIndicatorColorSpecifier> m_DepthIndicatorColorSpecifier;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
};