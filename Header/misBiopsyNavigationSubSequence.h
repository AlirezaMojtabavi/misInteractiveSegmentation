#pragma once

#include "misMultiViewSubSequence.h"

#include "misAutoCaptureScreenStrcts.h"
#include "IUserMessageBoardManager.h"
#include "ApproachAndModelInformationStrct.h"
#include "IBiopsyToolTransformCalculatorNav.h"
#include "misNavigationGUIEvents.h"
#include "IPlanEntryModifier.h"
#include "CustomizeArcTan.h"
#include "IAutomaticVirtualTipUpdater.h"
#include "IPlanTargetModifier.h"
#include "PlanTargetIsPassedNotifier.h"
#include "IPlanCreator.h"
#include "IPlanNavigationVisualizer.h"
#include "IPositionInPlanCoordinateSystemCalculatorSetter.h"
#include "IPilotIndicatorColorSpecifier.h"
#include "IBiopsyNavigationUiUpdater.h"
#include "IUpdateLayoutToDynamicLayout.h"
#include "INavigationPackageChanger.h"
#include "IUpdatePlaning.h"
#include "IShowCurrentPackage.h"
#include "misEntNavigationSubSequence.h"
#include "IVolumeCropping.h"
#include "IScrewPlanView.h"
#include "TargetingAnnotation.h"

class IGroupViewerFactory;
class IGroupViewerSettingFinder;
class INavigationLayoutFactory;
class INavigationLayout;
class INavigationTrackingHelper;
class IViewerRepository;
class ITreeViewUIUpdater;
class misTrackerImageSynchronizer;
class IPanoramicTransformConverter;
class IPlanningNavigation;
class IGeneralNavigationHelper;
class IPackageDataVisualizer;
class misWindow;
class misTrackingStateReport;
class ITrackerImageSynchronizer;
class IDatasetManager;
class INavigationPackageFinder;
class misPlanData;
class Iwindows;
class IToolShapeBuilder;
class IFixedPointsDistanceMeasurment;
class ITargetDistanceMeasurement;
class ICheckPointsDistanceMeasurement;

using namespace parcast;

namespace parcast
{
	class VisibilityManagement;
	class PlanTransformUpdater;
	class IToolRepresentationDecider;
	class IToolRepresentationDecider;
}

class misBiopsyNavigationSubSequence : public misMultiViewSubSequence
{
public:

	void UpdateTartgetAnnoatation();
	misBiopsyNavigationSubSequence(
		std::shared_ptr<IBiopsyToolTransformCalculatorNav> toolTransformCalculator,
		std::shared_ptr<INavigationLayout> layout,
		std::shared_ptr<INavigationTrackingHelper> trackingHelper,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
		std::shared_ptr<IFixedPointsDistanceMeasurment> fixedPointsDistanceMeasurment,
		std::shared_ptr<ITargetDistanceMeasurement>  targetDistanceMeasurement,
		std::shared_ptr<ICheckPointsDistanceMeasurement> checkPointsDistanceMeasurement,
		std::shared_ptr<ITrackerImageSynchronizer> trackerImageSynchronizer,
		std::shared_ptr<IGeneralNavigationHelper> generalNavigationHelper,
		std::shared_ptr<IBiopsyNavigationUiUpdater> navigationUIUpdater,
		std::shared_ptr<ITreeViewUIUpdater> treeViewUIUpdater,
		std::shared_ptr<INavigationPackageFinder> navigationPackageFinder,
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
		std::shared_ptr<IViewerRepository> viwerRepo,
		std::weak_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<ISubsequenceLayout> model,
		std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorSetter> positionInPlanCoordinateSystemCalculator,
		std::shared_ptr<IPlanNavigationVisualizer> planNavigationVisualizer,
		std::shared_ptr<IPlanEntryModifier> planEntryModifier,
		std::shared_ptr<IPlanCreator> planCreator,
		CustomizeArcTan expFunction,
		std::unique_ptr<IAutomaticVirtualTipUpdater> automaticVirtualTipUpdater,
		std::shared_ptr<IPilotIndicatorColorSpecifier> crossIndicatorColorSpecifier,
		std::shared_ptr<IPilotIndicatorColorSpecifier> circleIndicatorColorSpecifier,
		std::shared_ptr<IPilotIndicatorColorSpecifier> depthIndicatorColorSpecifier,
		std::shared_ptr<IUpdateLayoutToDynamicLayout> updateLayoutToDynamicLayout,
		std::shared_ptr<IUpdatePlaning> updatePlaning,
		std::shared_ptr<IShowCurrentPackage> showCurrentPackage,
		std::shared_ptr<INavigationSubsequenceInitializer> navigationSubsequenceInitializer,
		std::shared_ptr<INavigationPackageChanger> navigationPackageChanger,
		std::shared_ptr<misSoftwareInformation> softwareInformation,
		std::shared_ptr<IVolumeCropping> volumeCorpping,
		std::shared_ptr<parcast::IScrewPlanView> screwPlanView);

	misBiopsyNavigationSubSequence(std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<IGeneralNavigationHelper> navHelper,
		IDatasetManager* datasetManager,
		std::shared_ptr<INavigationTrackingHelper> trackingHelper,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
		std::shared_ptr<IUserMessageBoardManager> messageBoard,
		std::shared_ptr<IBiopsyNavigationUiUpdater> navigationUpdater,
		std::shared_ptr<ITreeViewUIUpdater> treeUpdater,
		std::shared_ptr<INavigationPackageFinder> packageFinder,
		std::shared_ptr<misTrackerImageSynchronizer> toolSyncer,
		const std::string& sequenceName,
		const std::string& subsequenceName,
		std::shared_ptr<ISubsequenceLayout> model,
		CustomizeArcTan expFunction,
		std::unique_ptr<IAutomaticVirtualTipUpdater> automaticVirtualTipUpdater,
		std::shared_ptr<IUpdateLayoutToDynamicLayout> updateLayoutToDynamicLayout,
		std::shared_ptr<IUpdatePlaning> updatePlaning,
		std::shared_ptr<IShowCurrentPackage> showCurrentPackage,
		std::shared_ptr<INavigationSubsequenceInitializer> navigationSubsequenceInitializer,
		std::shared_ptr<misSoftwareInformation> softwareInformation,
		std::shared_ptr<IVolumeCropping> volumeCropping,
		std::shared_ptr<parcast::IScrewPlanView> screwPlanView);
	void SelectEntryPoint();
	void SelectTargetPoint();

	void AddPilot();
	void UpdatePlanTargetRadiusSliderInGui();
	void UploadAllTextures(const ImageListTypedef& images);
	void OnSelected();
	void UpdateSettingFromAppSetting();
	void SetVirtualTip(double lenght);
	void Render();
	void TaskOnLeave();
	void UpdateStatus(long long int puls);
	void ResetSetting();
	void RealseAllResources();
	void FindDefaultPackage(const std::string& registeredImageUID);
	void ShowCurrentPackage(std::shared_ptr<ISimpleDataPackage> package);
	void UpdateTargetRegionRadius(double radius);
	bool ProcessRequest(misGUIEvent* pEvent);


	misEventListTypedef GetEventToGui();
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;
	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;

private:

	bool ChangePackge(const std::string& packuid);
	void UpdateByTrackingStatus();
	void UpdatePlaning();
	void UpdateImageSettingPanelPropertiesGUI();
	void SetStatusMessage(misTrackingStateReport toolsStatus);
	void UpdateLayoutToDynamicLayout(std::string layout);
	void SwitchToStandardLayout();
	void RemoveTargtingAnnotations();
	void UpdateLayoutListInUI();
	void UpdateToolSynsc();
	std::weak_ptr<IPlan> GetFirstVisibleScrewPlan();
	double Distance2D(double x, double y) const;
	IPilotIndicatorColorSpecifier::IndicatorColor GetWorstColor(IPilotIndicatorColorSpecifier::IndicatorColor color_1, IPilotIndicatorColorSpecifier::IndicatorColor color_2) const;



	std::shared_ptr<IGeneralNavigationHelper> m_GeneralNavigationHelper;
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<INavigationPackageFinder> m_PackageFinder;
	std::shared_ptr<const ITransform> m_NavigationCalibrationTransform;
	std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorSetter> m_PositionInPlanCoordinateSystemCalculator;
	std::shared_ptr<IPlanNavigationVisualizer> m_PlanNavigationVisualizer;
	std::shared_ptr<IPanoramicTransformConverter> m_PanoramicSliceViewSettings;
	std::shared_ptr<IUserMessageBoardManager> m_MessageBoardManager;
	std::shared_ptr<INavigationTrackingHelper>  m_TrackingHelper;
	std::weak_ptr<IPlan> m_CurrentPlannedScrew;
	std::shared_ptr<IBiopsyNavigationUiUpdater> m_NavigationUIUpdater;
	std::shared_ptr<ITrackerImageSynchronizer> m_ToolSync;
	std::shared_ptr<ISubsequenceLayout> m_UiModel;
	std::shared_ptr<IViewerRepository> m_ViewerRepo;
	std::shared_ptr<ITreeViewUIUpdater> m_TreeViewUiUpdater;
	std::shared_ptr<Iwindows> m_PilotWindow;
	std::shared_ptr<PlanTransformUpdater> m_PlanTransformUpdater;
	std::shared_ptr<VisibilityManagement> m_VisibilityMangement;
	std::shared_ptr<INavigationLayout> m_NavigationLayout;
	std::shared_ptr<IToolShapeBuilder> m_ToolBuilder;
	std::shared_ptr<IToolRepresentationDecider> m_Decider;
	std::shared_ptr<IFixedPointsDistanceMeasurment> m_FixedPointsDistanceMeasure;
	std::shared_ptr<ITargetDistanceMeasurement> m_DistanceToTarget;
	std::shared_ptr<ICheckPointsDistanceMeasurement> m_DistanceToCheckPoint;

	misCaptureScreenStatus m_CaptureStatus = unsetCaptureScreen;
	IUserMessageBoardManager::MessageId m_NavigationToolVisibilityMsgId = 0;
	IUserMessageBoardManager::MessageId m_ReferenceToolVisibilityMsgId = 0;
	IUserMessageBoardManager::MessageId m_InterferenceMsgId = 0;
	IUserMessageBoardManager::MessageId m_PackageSelectedMsgId = 0;

	double m_AutomaticGotoFullScreenWindowValue;
	double m_lastPointerDistanceToTargetPoint;
	double m_lastTakingSnapshotValue;
	double m_AngleStep = 1;

	bool m_FreezState = false;
	bool m_LastMeasurementStatus;
	IDatasetManager* m_DataSetManger;
	ApproachAndModelInformationStrct m_SelectedObjectInformation;
	std::shared_ptr<misWindow> m_PilotWin;
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::weak_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<IScrewPlanView> m_ScrewPlanView;
	std::shared_ptr<IBiopsyToolTransformCalculatorNav> m_ToolTransformCalculator;
	std::shared_ptr<IPlanEntryModifier> m_PlanEntryModifier;
	CustomizeArcTan m_ExpFunction;
	std::unique_ptr<IAutomaticVirtualTipUpdater> m_AutomaticVirtualTipUpdater;
	std::unique_ptr<IPlanTargetModifier> m_PlanTargetModifier;
	std::string m_LastSelectedLayout;
	std::unique_ptr<PlanTargetIsPassedNotifier> m_PlanTargetIsPassedNotifier;
	std::shared_ptr<IPlanCreator> m_PlanCreator;
	std::shared_ptr<IPilotIndicatorColorSpecifier> m_CrossIndicatorColorSpecifier;
	std::shared_ptr<IPilotIndicatorColorSpecifier> m_CircleIndicatorColorSpecifier;
	std::shared_ptr<IPilotIndicatorColorSpecifier> m_DepthIndicatorColorSpecifier;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<INavigationPackageChanger> m_NavigationPackageChanger;
	std::shared_ptr<IUpdateLayoutToDynamicLayout> m_UpdateLayoutToDynamicLayout;
	std::shared_ptr<IUpdatePlaning> m_UpdatePlaning;
	std::shared_ptr<IShowCurrentPackage> m_ShowCurrentPackage;
	std::shared_ptr<INavigationSubsequenceInitializer> m_NavigationSubsequenceInitializer;
	std::shared_ptr<IVolumeCropping> m_VolumeCropper;
	std::vector<std::shared_ptr<parcast::TargetingAnnotation>> m_targetingAnnotations;
};