#pragma once

#include "IApplicationWorkflow.h"
#include "ICoordinateSystemCorrelationManager.h"
#include "ISettingsContainer.h"
#include "IWorkflowStep.h"
#include "misDataBaseManager.h"
#include "misDataSetManager.h"
#include "misDataUploadingWorkflowStep.h"

// In this class we handle and manage the navigation between steps and other properties and objects that must be available 
// in the ENT surgery type application workflow.
class misEntApplicationWorkflow : public IApplicationWorkflow
{
public:
	// By this constructor we give all the objects that are needed in steps of the workflow
	misEntApplicationWorkflow(std::shared_ptr<ISettingsContainer> applicationSettings,
		std::shared_ptr< ICoordinateSystemRepository > coordSysRepo,
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager,
		misDatasetManager* datasetManager, std::shared_ptr<misDataBaseManager> databaseManager);

	MIS_HAS_EVENTS_IMPLEMENTATION;

	// IApplicationWorkflow interface:
	MIS_DEFINE_EVENT_IMPLEMENTATION(CurrentStepChanged);
	MIS_DEFINE_EVENT_IMPLEMENTATION(StepAvailabilityChanged);
	virtual StepIdType GetCurrentWorkflowStepId() const override;
	virtual void SetCurrentWorkflowStepId( const StepIdType& workflowStepId ) override;
	virtual bool IsStepAvailable( const StepIdType& stepId ) const override;
	virtual void UpdateStatus() const override;

	// Other methods:
	// Methods retrieving individual steps contained within this workflow object.
	std::shared_ptr<misDataUploadingWorkflowStep> GetHomeStep() const;
	std::shared_ptr<misDataUploadingWorkflowStep> GetDataUploadingStep() const;
	std::shared_ptr<misDataUploadingWorkflowStep> GetDataCheckingStep() const;

private:
	const StepIdType HomeId, DataUploadingId, DataCheckingId, SegmentationId, PlanningId, LandmarkSelectionId, 
		LandmarkRegistrationId, SurfaceRegistrationId, NavigationId;

	// map object that relates all steps by their id to their workflow object
	std::map< StepIdType, std::shared_ptr<IWorkflowStep> > m_WorkflowSteps;
	
	// An object that ensures consistent calling of enter and leave procedure of each step at the correct instant.
	std::shared_ptr<IWorkflowStep> m_CurrentWorkflowStep;

	misDatasetManager* m_DatasetManager;
	std::shared_ptr<misDataBaseManager> m_DatabaseManager;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CorrelationManager;
	std::shared_ptr<ICoordinateSystemRepository> m_CoordSysRepo;
	std::shared_ptr<ISettingsContainer> m_ApplicationSettings;
};