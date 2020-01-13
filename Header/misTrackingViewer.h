#pragma once

#include "ITrackingToolQuery.h"
#include "ITrackingToolRepository.h"
#include "mis3DViewer.h"
#include "misEventProxy.h"
#include "misSurfaceRepresentation.h"
#include "misTrackingManagerEnums.h"
#include "misTrackingToolQuery.h"
#include "misTransformType.h"
#include "ITrackerConfigure.h"

class misTrackingViewer : public misEventProxy
{
public:
	virtual bool ProcessRequest(misGUIEvent* pEvent);
	void InitialeGuiProcessing(std::shared_ptr<Iwindows> trackingViewerWindow);
	void UpdateStatus();
	void MakeCameraFrustumPlane();
	void UpdateXYZView();
	void AddTool2TrackingViewerWindow(std::shared_ptr<ITrackingTool> tool);
	void AddCameraObject() const;
	void SetTrackerConfig(std::shared_ptr<ITrackerConfigure> val);
	typedef misTrackingViewer					Self;
	typedef itk::SmartPointer<Self>			Pointer;
	misTrackingViewer(std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > csCorrelationManager, TrackerType type);
	std::shared_ptr<mis3DViewer>		m_ToolViewer;
	misApplicationSetting*	m_pAppSetting;	
	igstk::Tracker*	m_Tracker;
	ITrackingToolRepository::TrackerToolListType m_Tools;
	
private:
	std::shared_ptr<ITrackingToolQuery> m_ToolLocator;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	misTransformType m_LastToolTransformComputationType;
	TrackerType m_TrackerType;
	std::shared_ptr<ITrackerConfigure> m_TrackerConfig;

};

