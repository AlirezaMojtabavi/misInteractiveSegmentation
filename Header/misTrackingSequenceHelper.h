#pragma once
#include "misToolProperties.h"
#include "misTrackingStateReporter.h"
#include <memory>
#include "misTrackingToolMarkerReporter.h"
#include "misToolRepresentation.h"
#include "mis3DViewer.h"
#include "misTrackingManagerObserver.h"
#include "../misTrackingSequenceLib/ITrackingSequenceHelper.h"
#include "ITrackerConfigure.h"

class misGUIEvent;

// The misTrackingSequenceHelper class used for general functionality needed by configing any type of tracker
class misTrackingSequenceHelper :public ITrackingSequenceHelper
{
public:
	misTrackingSequenceHelper(std::shared_ptr<ITrackerConfigure> trackerInitilizer, igstk::Tracker::Pointer tracker);
	
	bool ToolExistsInXMLlist(misToolPropertiesListTypdef xmlList, std::pair<ULONG, int> OneDetectedTool) override;
	std::shared_ptr<misTrackingStateReporter> GetToolStateReporter() override;
	std::shared_ptr<misTrackingToolMarkerReporter> GetToolMarkerReporter(std::shared_ptr<const ITrackingTool> tool)  override;
	void SetLogger(misOldObject::LoggerType * logger) override;
	std::vector<std::shared_ptr<I3DViewer>> GetAllViewers();
	void RealseAllResources();
	void AddToolToWindow(std::shared_ptr<I3DViewer> viewer, std::shared_ptr<ITrackingTool> tool);
	void UpdateStatus(long long puls);
	void InitializeRenderingView() const;
	void ActivateFpsRepresetation();
	void Render();
	void AddTrackerTool(std::shared_ptr<ITrackingTool> pTracker);
	void ResetSetting();
	void AddRepresentation(std::shared_ptr<misRepresentation> surface);
	bool ConnectToTracker(ISettingsContainer::StringList toolNames);
	void InitializeViewer(std::shared_ptr<Iwindows> eFront, std::shared_ptr<Iwindows> side, std::shared_ptr<Iwindows> top,
		std::shared_ptr<Iwindows> Viewer3d) override;

	std::shared_ptr<I3DViewer> GetFrontView() const;
	std::shared_ptr<I3DViewer> GetSideView() const;
	std::shared_ptr<I3DViewer> GetTopView() const;
	std::shared_ptr<I3DViewer> Get3DView() const;
	void SetCSCorrelationManager(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlarionTree);
	void SetParent(itk::Object::Pointer parent);
	igstk::Tracker::Pointer GetTracker() const;
	ISettingsContainer::StringList GetToolNames() const { return m_ToolNames; }
	void SetToolNames(ISettingsContainer::StringList val);
	std::shared_ptr<ITrackerConfigure> GetTrackingInitializer() const { return m_TrackingInitializer; }
	std::shared_ptr<misTrackingToolQuery> GetToolQuery() const;
private:

	bool ToolAreLoaded() const;
	void CreateToolQuery();


	igstk::Tracker::Pointer	m_Tracker;
	std::shared_ptr<ITrackerConfigure>	m_TrackingInitializer;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	std::vector<misToolRepresentation*> m_ToolList1;
	std::vector<misToolRepresentation*> m_ToolList2;
	std::vector<misToolRepresentation*> m_ToolList3;
	std::vector<misToolRepresentation*> m_ToolList4;
	std::shared_ptr<I3DViewer>  m_FrontView;
	std::shared_ptr<I3DViewer>  m_SideView;
	std::shared_ptr<I3DViewer>  m_TopView;
	std::shared_ptr<I3DViewer>  m_3DViewTracking;
	std::string m_SequenceName;
	std::string m_SubsequenceName;
	itk::Object::Pointer m_ParentEventInvoker;
	bool m_TrackerDisconnectMsgAlreadyShown;
	misLogger* m_Logger;
	ISettingsContainer::StringList m_ToolNames;
	std::shared_ptr<misTrackingToolQuery> m_ToolQuery;
	std::shared_ptr<misTrackingStateReporter> m_Reporter;
	std::map<std::string, std::shared_ptr<misTrackingToolMarkerReporter>> m_Reporters;

};
