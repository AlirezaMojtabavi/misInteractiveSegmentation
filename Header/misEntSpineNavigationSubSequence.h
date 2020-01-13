//
#pragma once

#include "IPanoramicTransformConverter.h"
#include "IPlanningNavigation.h"
#include "IUserMessageBoardManager.h"
#include "misAutoCaptureScreenStrcts.h"
#include "misEventFromGui.h"
#include "misGeneralNavigationHelper.h"
#include "misNavigationTrackingHelper.h"
#include "misSubSeqTreeViewEventProcessor.h"
#include "IENTSpineNavigationUIUpdater.h"

class misEntSpineNavigationSubSequence : public misMultiViewSubSequence
{
public:	
	~misEntSpineNavigationSubSequence(void);

	igstkStandardClassBasicTraitsMacro( misEntSpineNavigationSubSequence , misMultiViewSubSequence );
	
	static Pointer New();

	static Pointer New(
		INavigationViewersNView* groupViewer, 
		std::shared_ptr<IGeneralNavigationHelper> navHelper, 
		IDatasetManager* datasetManager, 
		std::shared_ptr<IPlanningNavigation> planNav, 
		std::shared_ptr<INavigationTrackingHelper> trackingHelper, 
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
		std::shared_ptr<IUserMessageBoardManager> messageBoard, 
		const std::string& sequenceName = "ENTSpineNavSeq", 
		const std::string& subsequenceName = "ENTSpineNavSubSeq");

	void AddTrackerTool(std::shared_ptr<ITrackingTool>   trackerToool);
		virtual void InitialeGuiProcessing(void) override;
	void OnSelected(void);

	void ClearPackageListTreeView();

	void UpdateSettingFromAppSetting();
	bool ProcessRequest(misGUIEvent* pEvent);

	void SetVirtualTip(double lenght);

	void Render(void);
	void TaskOnLeave( void );
	void UpdateStatus(long long int puls);
	void ResetSetting();
	void RealseAllResources(void);
	misEventListTypedef GetEventToGui();
	virtual void SetCSCorrelationManager(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val) override;

private:
	misEntSpineNavigationSubSequence();

	misEntSpineNavigationSubSequence(
		INavigationViewersNView* groupViewer, 
		std::shared_ptr<IGeneralNavigationHelper> navHelper, 
		IDatasetManager* datasetManager, 
		std::shared_ptr<IPlanningNavigation> planNav, 
		std::shared_ptr<INavigationTrackingHelper> trackingHelper, 
		std::shared_ptr<IPackageDataVisualizer> packageVisualizer,
		std::shared_ptr<IUserMessageBoardManager> messageBoard, 
		const std::string& sequenceName, 
		const std::string& subsequenceName);

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
 	void ShowTreeInformation();
	void UpdatePlaning();
	virtual void SetPackageContent();
	virtual void ShowTreePackageInGUI();
	virtual void ShowCurrentPackageContentsInViewer();
	virtual void ShowPackageListInGUI();
	void Update3DModelSettingPanelPropertiesGUI();
	void UpdateImageSettingPanelPropertiesGUI();
	void UpdataCroppingDirectionInGUI(void);
	void UpdateGuiMessageBoard ( const std::string& message, IUserMessageBoardManager::MessageSeverity severity );
	void SetStatusMessage( misTrackingStateReport toolsStatus );

	std::shared_ptr<IGeneralNavigationHelper> m_GeneralNavigationHelper;
	std::shared_ptr<IPackageDataVisualizer> m_PackageVisualizer;
	std::shared_ptr<const ITransform> m_NavigationCalibrationTransform; // keep navigation tool transform
	std::shared_ptr<IPlanningNavigation> m_PlanNavigation;
	std::shared_ptr<IPanoramicTransformConverter> m_PanoramicSliceViewSettings;
	misCaptureScreenStatus   m_CaptureStatus;
	std::shared_ptr<IUserMessageBoardManager> m_MessageBoardManager;
	IUserMessageBoardManager::MessageId m_NavigationToolVisibilityMsgId;
	IUserMessageBoardManager::MessageId m_ReferenceToolVisibilityMsgId;
	IUserMessageBoardManager::MessageId m_InterferenceMsgId;
	IUserMessageBoardManager::MessageId m_PackageSelectedMsgId;
	double m_AutomaticGotoFullScreenWindowValue;
	bool m_FreezState;
	double m_lastPointerDistanceToTargetPoint;
	double m_lastTakingSnapshotValue;
	IDatasetManager* m_DataSetManger;
	INavigationViewersNView* m_NavigationNView;
	//Saves info about selected package and how we are going to show it.
	ApproachAndModelInformationStrct m_SelectedObjectInformation;
	std::shared_ptr<INavigationTrackingHelper>  m_TrackingHelper;
	std::shared_ptr<misPlanData> m_CurrentPlannedScrew;
	std::shared_ptr<IENTSpineNavigationUIUpdater> m_NavigationUpdater;
};