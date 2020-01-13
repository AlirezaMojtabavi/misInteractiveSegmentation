#pragma once
#include "misMultiViewSubSequence.h"
#include "misAuroraTracker.h"
#include "misAutoCaptureScreenStrcts.h"
#include "IOpenGLContextSharing.h"
#include "INavigationSubsequneInitilizer.h"
#include "IUpdatePlaning.h"
#include "IShowCurrentPackage.h"
#include "INavigationPackageChanger.h"
#include "IUpdateLayoutToDynamicLayout.h"
#include "misCreateCompositeSubSeq.h"
#include "IVolumeCropping.h"
#include "IScrewPlanView.h"

class IToolShapeBuilder;
class ITargetDistanceMeasurement;
class IPanoramicTransformConverter;
class INavigationTrackingHelper;
class ITrackerImageSynchronizer;
class IViewerRepository;
class ICheckPointsDistanceMeasurement;
class IFixedPointsDistanceMeasurment;
class misTrackerImageSynchronizer;
class INavigationPackageFinder;
class ITreeViewUIUpdater;
class IENTNavigationUIUpdater;
class IPackageDataVisualizer;
class IPlanningNavigation;
class IDatasetManager;
class IGeneralNavigationHelper;
class IGroupViewerFactory;
class INavigationLayoutFactory;
class INavigationLayout;

namespace parcast
{
	class VisibilityManagement;
	class IToolRepresentationDecider;
}

using namespace parcast;

enum class SOURCEDEST;

class misEntNavigationSubSequence : public misMultiViewSubSequence
{
public:
	misEntNavigationSubSequence(
		std::shared_ptr<INavigationLayout> layout,
		std::shared_ptr<INavigationTrackingHelper> trackingHelper,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
		std::shared_ptr<IToolShapeBuilder> toolBuilder,
		std::shared_ptr<IToolRepresentationDecider> decider,
		std::shared_ptr<IFixedPointsDistanceMeasurment> fixedPointsDistanceMeasurment,
		std::shared_ptr<ITargetDistanceMeasurement>  targetDistanceMeasurement,
		std::shared_ptr<ICheckPointsDistanceMeasurement> checkPointsDistanceMeasurement,
		std::shared_ptr<ITrackerImageSynchronizer> trackerImageSynchronizer,
		std::shared_ptr<IGeneralNavigationHelper> generalNavigationHelper,
		std::shared_ptr<IENTNavigationUIUpdater> entNavigationUIUpdater,
		std::shared_ptr<ITreeViewUIUpdater> treeViewUIUpdater,
		std::shared_ptr<INavigationPackageFinder> navigationPackageFinder,
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
		std::shared_ptr<IViewerRepository> viwerRepo,
		std::weak_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<ISubsequenceLayout> model,
		std::shared_ptr<IUpdatePlaning> updatePlaning,
		std::shared_ptr<IShowCurrentPackage> showCurrentPackage,
		std::unique_ptr<INavigationSubsequenceInitializer> navigationSubsequenceInitializer,
		std::shared_ptr<INavigationPackageChanger> m_NavigationPackageChanger,
		std::shared_ptr<IUpdateLayoutToDynamicLayout> m_UpdateLayoutToDynamicLayout,
		std::shared_ptr<misSoftwareInformation> softwareInformation,
		std::shared_ptr<IVolumeCropping> volumeCropping, 
		std::shared_ptr<parcast::IScrewPlanView> screwPlanView);

	misEntNavigationSubSequence(std::shared_ptr<INavigationLayout> layout,
		std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<IGeneralNavigationHelper> navHelper,
		IDatasetManager* datasetManager,
		std::shared_ptr<INavigationTrackingHelper> trackingHelper,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
		std::shared_ptr<IENTNavigationUIUpdater> navigationUpdater,
		std::shared_ptr<ITreeViewUIUpdater> treeUpdater,
		std::shared_ptr<INavigationPackageFinder> packageFinder,
		std::shared_ptr<ITrackerImageSynchronizer> toolSyncer,
		const std::string& sequenceName,
		const std::string& subsequenceName,
		std::shared_ptr<ISubsequenceLayout> model,
		std::shared_ptr<IUpdatePlaning> updatePlaning,
		std::shared_ptr<IShowCurrentPackage> showCurrentPackage,
		std::unique_ptr<INavigationSubsequenceInitializer> navigationSubsequenceInitializer,
		std::shared_ptr<misSoftwareInformation> softwareInformation,
		std::shared_ptr<IVolumeCropping> volumeCropping,
		std::shared_ptr<parcast::IScrewPlanView> screwPlanView
	);

	void SetObliqueMode(bool isObliqueView);
	void SetMeasurment2PointState(SOURCEDEST location);
	void SetFreezState(bool freezeState);
	void ChangeToStandardLayoutEvent();
	void CHnagePackage(misApproachAndModelTreeViewClicked::PayloadType item);
	void SetViwersToToolSync();

	void OnSelected();
	void UpdateSettingFromAppSetting();
	void ReInitilzeViewers(std::shared_ptr<IGroupViewerSetting> layout);
	void SetVirtualExtend(double lenght);
	void Render();
	void TaskOnLeave();
	void UpdateStatus(long long int puls);
	void ResetSetting();
	void RealseAllResources();
	void UpdateLayoutToDynamicLayout(std::string layout);

	bool ProcessRequest(misGUIEvent* pEvent);
	misEventListTypedef GetEventToGui();
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	void UpdateGroupViewer();
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;
	virtual misUID FindDefaultPackage(std::string reference);
	void ShowCurrentPackage(std::shared_ptr<ISimpleDataPackage> package);

private:

	template <class EventType, typename PayloadType>
	void InvokeLoadedEvent(const PayloadType& payload)
	{
		EventType ev;
		ev.SetSequenceName(m_SequenceName);
		ev.SetSubTab(m_SubsequenceName);
		ev.Set(payload);
		InvokeEvent(ev);
	}
	template <class EventType>
	void InvokeUnloadedEvent()
	{
		EventType ev;
		ev.SetSequenceName(m_SequenceName);
		ev.SetSubTab(m_SubsequenceName);
		InvokeEvent(ev);
	}

	void InitializeObject();
	void UpdateByTrackingStatus();
	void ShowTreePackageInGUI();
	virtual void ShowCurrentPackageContentsInViewer();

	template <class EventType, typename PayloadType>
	void InvokeParentLoadedEvent(const PayloadType& payload)
	{
		EventType ev;
		ev.Set(payload);
		ev.SetSequenceName(m_SequenceName);
		ev.SetSubTab(m_SubsequenceName);
		InvokeEvent(ev);
	}

	template <class EventType>
	void InvokeParentUnloadedEvent()
	{
		EventType ev;
		ev.SetSequenceName(m_SequenceName);
		ev.SetSubTab(m_SubsequenceName);
		InvokeEvent(ev);
	}

	void UpdateUIVisibilityIndicators(misGUIEvent* pEvent);

public:
	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;
private:
	std::shared_ptr<IGeneralNavigationHelper> m_GeneralNavigationHelper;
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<INavigationPackageFinder> m_PackageFinder;
	std::shared_ptr<const ITransform> m_NavigationCalibrationTransform;
	std::shared_ptr<IPanoramicTransformConverter> m_PanoramicSliceViewSettings;
	std::shared_ptr<ITreeViewUIUpdater> m_TreeViewUiUpdater;
	std::shared_ptr<INavigationTrackingHelper>  m_TrackingHelper;
	std::weak_ptr<misPlanData> m_CurrentPlannedScrew;
	std::shared_ptr<IENTNavigationUIUpdater> m_NavigationUIUpdater;
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::shared_ptr<IFixedPointsDistanceMeasurment> m_FixedPointsDistanceMeasure;
	std::shared_ptr<ITargetDistanceMeasurement> m_DistanceToTarget;
	std::shared_ptr<ICheckPointsDistanceMeasurement> m_DistanceToCheckPoint;
	std::shared_ptr<ITrackerImageSynchronizer> m_ToolSync;
	std::shared_ptr<IViewerRepository> m_ViewerRepo;
	std::shared_ptr<ISubsequenceLayout> m_UiModel;
	std::shared_ptr<VisibilityManagement> m_VisibilityManagement;
	std::shared_ptr<INavigationLayout> m_NavigationLayout;
	std::weak_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<IToolShapeBuilder> m_ToolBuilder;
	std::shared_ptr<IToolRepresentationDecider> m_Decider;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<IUpdatePlaning> m_UpdatePlaning;
	std::shared_ptr<IShowCurrentPackage> m_ShowCurrentPackage;
	std::shared_ptr<INavigationSubsequenceInitializer> m_NavigationSubsequenceInitializer;
	std::shared_ptr<INavigationPackageChanger> m_NavigationPackageChanger;
	std::shared_ptr<IUpdateLayoutToDynamicLayout> m_UpdateLayoutToDynamicLayout;


	IDatasetManager* m_DataSetManger;
	misCaptureScreenStatus m_CaptureStatus;
	double m_lastPointerDistanceToTargetPoint;
	double m_AutomaticGotoFullScreenWindowValue;
	double m_lastTakingSnapshotValue;
	bool m_FreezState;
	bool m_MeasurmentActive;
	bool m_LastMeasurementStatus;
	std::string m_LastSelectedLayout;
	std::shared_ptr<IVolumeCropping> m_VolumeCropper;
	std::shared_ptr<parcast::IScrewPlanView> m_ScrewPlanView;
};
