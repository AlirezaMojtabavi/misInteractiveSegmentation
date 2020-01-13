#pragma once

#include "IWorkflowStep.h"
#include "misEventMacros.h"

//////////////////////////////////////////////////////////////////////////
// This class represent the workflow of a smart surgery application and it manages the sequence that may occur in the current 
// workflow and handles the workflow step switching.
class IApplicationWorkflow
{
public:
	typedef std::string StepIdType;
	MIS_HAS_EVENTS_INTERFACE;

	// The CurrentStepChanged event is raised whenever the current step is changed.
	MIS_DEFINE_EVENT_INTERFACE(CurrentStepChanged, const StepIdType& previousStepId, const StepIdType& currentStepId);

	// The StepStatusChanged event is raised whenever the status of any of the contained steps is changed, that is, any of 
	// the workflow steps reports a status change.
	MIS_DEFINE_EVENT_INTERFACE(StepAvailabilityChanged, const StepIdType& stepId, bool isAvailable);

	// Get the ID of the current active workflow step.
	virtual StepIdType GetCurrentWorkflowStepId() const = 0;

	// Set the current Active workflow step for entering and handling this workflow step
	virtual void SetCurrentWorkflowStepId(const StepIdType& workflowStepId) = 0;

	// By this method we can know whether the specified by the step ID is enabled, and this status will 
	// be true for steps that whose Status is not Unavailable. false means the workflow step is not enabled/available.
	virtual bool IsStepAvailable(const StepIdType& stepId) const = 0;

	// This method update the status of the current step that is running in application and is called by the application object.
	// It is essential to smooth flow of the application that UpdateStatus be called at short regular intervals.
	virtual void UpdateStatus() const = 0; 
};