#pragma once
#ifndef misToolAccuracy_H
#define misToolAccuracy_H

#include "mis3DViewer.h"
#include "misApplicationSetting.h"
#include "misCalibrationEnums.h"
#include "misCalibrationWorkflowManager.h"
#include "misEventFromGui.h"
#include "misEventProxy.h"
#include "misGuiEvent.h"
#include "misMultiViewSubSequence.h"
#include "misTrackingToolQuery.h"
#include "misTransformType.h"
#include "stopwatch.h"
#include "ITrackerConfigure.h"
#include "StaticTransformUpdater.h"

class misToolAccuracySubSequence : public misSubSequence
{
public:

	misToolAccuracySubSequence(std::shared_ptr<ISubsequenceLayout> model,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager, std::shared_ptr<misSoftwareInformation> softwareInformation);
 
	~misToolAccuracySubSequence();
 
	typedef itk::Vector<double, 3> PointType;
	void SetSolutionProperties(std::shared_ptr<misSolutionProperty> solution);

	void InitialeGuiProcessing(std::shared_ptr<Iwindows> p_window);

	// Sets the subject tracking tool to be calibrated. Use IsBusy to make sure that no tool calibration is currently 
	// in progress before setting a new tool. Calling SetTool when tool accuracy is busy will cancel the current tool
	// calibration and revert it to the uncalibrated state.
	void SetTool(std::shared_ptr<ITrackingTool> tool);

	virtual bool ProcessRequest(misGUIEvent* pEvent);
	virtual misEventListTypedef GetEventToGui();
	
	// Determines whether the tool accuracy subsequence is presently busy calibrating a tracking tool.
	bool IsBusy() ;

	void SetTrackerConfig(std::shared_ptr<ITrackerConfigure> val);
private:
	typedef itk::Vector<double, 3> VectorType;



	struct ToolManagerState
	{
		misTransformType m_TransformComputationType;
		bool m_ToolVisibilityState;
	};

	// Read camera position and focal point in tool local coordinates (by loading 3d model and select proper position and focal 
	// point) - then transforming them in to global coordinates
	void UpdateViewOnCalibration();

	// Raises the CalibrationFinishedEvent after a certain amount of time is passed since the first call to this method. The
	// amount of time to wait is designated by a relevant application setting property. Optionally, a boolean value can be passed 
	// indicating whether steps required for accepting calibration should be taken. See AcceptCalibration().
	void SendCalibrationFinishedEventDelayed(bool acceptCalibration = false);

	void SendCalibrationFinishedEvent();

	// Raises the event to inform superordinates of the current state of calibration procedure.
	void SendCalibrationStatusUpdateEvent();

	// As a step in accepting calibration, serializes the tool properties containing applied calibration parameters back to the 
	// tracking tool XML file.
	void SerializeSubjectTool() const;

	// Takes the steps necessary to make the tracking tool usable and sets the status of the tracking tool to accepted 
	// to prevent subsequent repetition of calibration 	// on the same tool.
	void AcceptCalibration();

	// Sets the status of the tracking tool to uncalibrated so it might be calibrated at a later time.
	void DenyCalibration();

	// Gets the current visibility status of the tracking tools involved in calibration as part of the 
	// CalibrationStatusUpdate event data.
	ToolVisibilityStatus GetToolsVisibilityStatus();

	virtual void RealseAllResources() { }	// Pure virtual method in base
	void InitialeGuiProcessing() { }	// Pure virtual method in base

	// Pure virtual method in base, not sure why it's been declared there. Anyway we have our own use for it. We call it on each
	// pulse to update the status. It asks the workflow manager to update its status and raises appropriate signals according 
	// to its current status.
	void UpdateStatus(long long int puls);

	// Pure virtual method in base. Updates camera view and renders the tracking tool viewer, it is called in UpdateStatus().
	virtual void Render( void );
	
	// Called when tracker image is updated.
	void UpdateCameraImageCallBack(itk::Object *caller, const itk::EventObject & event);

	// Updates the current calibration tracking tool (the currently visible calibration tool) to be used and adds its
	// visual representation. 
	void UpdateCalibrationTool();

	// Gets [and lazy creates and initializes] the calibration workflow manager.
	std::shared_ptr<misCalibrationWorkflowManager> GetCalibrationWorkflowManager() ;

	// Get the currently visible calibration tracking tool that it retrieves using a misTrackingToolQuery object that it creates
	// and initializes on the fly if necessary.
	std::shared_ptr<ITrackingTool> GetVisibleCalibrationTrackingTool();

	virtual void SetCSCorrelationManager( std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > val );
	void Reset();
	void UpdateGuiMessageBoard ( const std::string& message, IUserMessageBoardManager::MessageSeverity severity );

	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
	misApplicationSetting* m_AppSetting;	
	std::shared_ptr<I3DViewer> m_ToolViewer;
	TrackerType m_TypeOfTracker;
	std::shared_ptr<ITrackingTool> m_CalibrationTool;
	std::shared_ptr<ITrackingTool> m_SubjectTool;
	itk::SmartPointer<igstk::Tracker> m_Tracker;
	long long int m_InternalTimer;
	Stopwatch m_AfterCalibrationWaitTimer;
	std::shared_ptr<misSolutionProperty> m_SolutionProperties;
	std::shared_ptr<IUserMessageBoardManager> m_MessageBoardManager;
	IUserMessageBoardManager::MessageId m_UpdateGuiMsgId;
	IUserMessageBoardManager::MessageId m_ToolVisibilityMsgId;
	std::shared_ptr<ITrackerConfigure> m_TrackerConfig;
	std::shared_ptr<ISubsequenceLayout> m_UiModel;
	std::shared_ptr<parcast::ICalibrationProfileFinder> m_CalibrationProfileFinder;
	std::shared_ptr<parcast::IStaticTransformUpdater> m_StaticTransformUpdater;
	std::shared_ptr<misCalibrationWorkflowManager> m_WorkflowManager;
	std::shared_ptr<misTrackingToolQuery> m_ToolQuery;

};

#endif
