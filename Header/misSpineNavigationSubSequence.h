#pragma once
#include "ApproachAndModelInformationStrct.h"
#include "CustomizeArcTan.h"
#include "INavigationLayout.h"
#include "IPilotIndicatorColorSpecifier.h"
#include "IPlanNavigationVisualizer.h"
#include "IPositionInPlanCoordinateSystemCalculatorSetter.h"
#include "IUserMessageBoardManager.h"
#include "PlanTransformUpdater.h"
#include "misAutoCaptureScreenStrcts.h"
#include "misMultiViewSubSequence.h"
#include "misWindow.h"
#include "IVolumeCropping.h"
#include "IScrewPlanView.h"

namespace parcast
{
	class VisibilityManagement;
}

class IPanoramicTransformConverter;
class IPlanningNavigation;
class IGeneralNavigationHelper;
class IDatasetManager;
class IPackageDataVisualizer;
class INavigationPackageFinder;
class INavigationTrackingHelper;
class misPlanData;
class IENTNavigationUIUpdater;
class misTrackingStateReport;
class ITrackerImageSynchronizer;
class Iwindows;

using namespace parcast;

class misSpineNavigationSubSequence : public misMultiViewSubSequence
{
public:

	misSpineNavigationSubSequence(
		std::weak_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
		std::shared_ptr<INavigationLayout> layotChanger,
		std::shared_ptr<INavigationPackageFinder> packageFinder,
		std::shared_ptr<ITrackerImageSynchronizer> trackerImageSynchronizer,
		std::shared_ptr<IGeneralNavigationHelper> generalNavigationHelper,
		std::shared_ptr<IENTNavigationUIUpdater> uiUpdater,
		std::shared_ptr<ISubsequenceLayout> model,
		std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorSetter> positionInPlanCoordinateSystemCalculator,
		std::shared_ptr<IPlanNavigationVisualizer> planNavigationVisualizer,
		std::shared_ptr<IPilotIndicatorColorSpecifier> pilotIndicatorsColorSpecifier,
		std::shared_ptr<INavigationTrackingHelper> trackingHelper, CustomizeArcTan expFunction,
		std::shared_ptr<IPilotIndicatorColorSpecifier> crossIndicatorColorSpecifier,
		std::shared_ptr<IPilotIndicatorColorSpecifier> circleIndicatorColorSpecifier,
		std::shared_ptr<IPilotIndicatorColorSpecifier> depthIndicatorColorSpecifier,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer, 
		std::shared_ptr<misSoftwareInformation> softwareInformation, 
		std::shared_ptr<IVolumeCropping> volumeCropping,
		std::shared_ptr<parcast::IScrewPlanView> screwPlanView);
	misSpineNavigationSubSequence(
		std::shared_ptr<INavigationViewersNView> groupViewer,
		std::shared_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManger,
		std::shared_ptr<IGeneralNavigationHelper> navHelper,
		IDatasetManager* datasetManager,
		std::shared_ptr<IPlanningNavigation> planNav,
		std::shared_ptr<INavigationTrackingHelper> trackingHelper,
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
		std::shared_ptr<IUserMessageBoardManager> messageBoard,
		std::shared_ptr<IENTNavigationUIUpdater> navigationUpdater,
		std::shared_ptr<INavigationPackageFinder> packageFinder,
		const std::string& sequenceName,
		const std::string& subsequenceName,
		CustomizeArcTan expFunction, 
		std::shared_ptr<misSoftwareInformation> softwareInformation, 
		std::shared_ptr<IVolumeCropping> volumeCropping,
		std::shared_ptr<parcast::IScrewPlanView> screwPlanView);

	virtual void AddPilot();
	void OnSelected();


	void ClearPackageListTreeView();
	void UpdateSettingFromAppSetting();
	bool ProcessRequest(misGUIEvent* pEvent);

	void UpdateToDefaultLayout();

	void SetVirtualTip(double lenght);
	void Render();
	void TaskOnLeave();
	void UpdateStatus(long long int puls);
	void ResetSetting();
	void RealseAllResources();
	misEventListTypedef GetEventToGui();
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers() override;
	std::vector<std::shared_ptr<IVolumeRenderer>> GetAllImageViewers() override;
	std::weak_ptr<INavigationViewersNView> GetGroupViewer() override;
	std::string FindDefaultPackage(std::string registeredImageUID);
	void UpdateLayoutToDynamicLayout(std::string layout);
	void ShowCurrentPackage(std::shared_ptr<ISimpleDataPackage>);
	void UpdateObliqueMode(bool isObliqueView);

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

	virtual void SetPackageContent();
	virtual void ShowCurrentPackageContentsInViewer();
	virtual void ShowPackageListInGUI();
	void InitializeObject();
	void UpdateByTrackingStatus();
	void UpdatePlaning();
	bool ChangePackge(std::string packuid);
	void Update3DModelSettingPanelPropertiesGUI();
	void UpdateImageSettingPanelPropertiesGUI();
	void UpdataCroppingDirectionInGUI();
	void UpdateGuiMessageBoard(const std::string& message, IUserMessageBoardManager::MessageSeverity severity);
	void SetStatusMessage(misTrackingStateReport toolsStatus);
	void UpdateLayoutListInUI();

public:
	std::vector<std::shared_ptr<IVolumeSlicer>> GetAllVolumeSlicers() override;
	std::vector<std::shared_ptr<IVolume3DRenderer>> GetVolume3DRenderer() override;
private:
	std::shared_ptr<INavigationTrackingHelper>  m_TrackingHelper;
	std::weak_ptr<misPlanData> m_CurrentPlannedScrew;
	std::shared_ptr<IENTNavigationUIUpdater> m_NavigationUIUpdater;
	std::shared_ptr<ITrackerImageSynchronizer> m_ToolSync;
	std::shared_ptr<ISubsequenceLayout> m_UiModel;
	std::shared_ptr<Iwindows> m_PilotWindow;
	std::shared_ptr<VisibilityManagement> m_VisibilityManagement;
	std::weak_ptr<INavigationViewersNView> m_GroupViewer;
	std::shared_ptr<ISimpleDataPackage> m_CurrentPackage;
	std::shared_ptr<IGeneralNavigationHelper> m_GeneralNavigationHelper;
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<INavigationPackageFinder> m_PackageFinder;
	std::shared_ptr<const ITransform> m_NavigationCalibrationTransform;
	std::shared_ptr<IPositionInPlanCoordinateSystemCalculatorSetter> m_PositionInPlanCoordinateSystemCalculator;
	std::shared_ptr<IPlanNavigationVisualizer> m_PlanNavigationVisualizer;
	std::shared_ptr<IPanoramicTransformConverter> m_PanoramicSliceViewSettings;
	std::shared_ptr<IUserMessageBoardManager> m_MessageBoardManager;
	std::shared_ptr<IPilotIndicatorColorSpecifier> m_PilotIndicatorsColorSpecifier;
	std::shared_ptr<IPlanningNavigation> m_PlanningNavigation;

	IDatasetManager* m_DataSetManger;
	misCaptureScreenStatus m_CaptureStatus;
	ApproachAndModelInformationStrct m_SelectedObjectInformation;
	IUserMessageBoardManager::MessageId m_NavigationToolVisibilityMsgId;
	IUserMessageBoardManager::MessageId m_ReferenceToolVisibilityMsgId;
	IUserMessageBoardManager::MessageId m_InterferenceMsgId;
	IUserMessageBoardManager::MessageId m_PackageSelectedMsgId;
	std::shared_ptr<PlanTransformUpdater> m_PlanTransformUpdater;
	std::shared_ptr<misWindow> m_PilotWin;
	std::shared_ptr<IPilotIndicatorColorSpecifier> m_CrossIndicatorColorSpecifier;
	std::shared_ptr<IPilotIndicatorColorSpecifier> m_CircleIndicatorColorSpecifier;
	std::shared_ptr<IPilotIndicatorColorSpecifier> m_DepthIndicatorColorSpecifier;
	std::shared_ptr<INavigationLayout>  m_NavigationLayout;
	CustomizeArcTan m_ExpFunction;
	bool m_LastMeasurementStatus;
	bool m_FreezState;
	double m_AngleStep = 10;
	std::string m_LastSelectedLayout;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::shared_ptr<IVolumeCropping> m_VolumeCropper;
	std::shared_ptr<parcast::IScrewPlanView> m_ScrewPlanView;

};