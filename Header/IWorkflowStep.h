#pragma once

#include "misEventMacros.h"

// This is the abstract class for all the steps that will be ready in the application. Each step is inherited from this class.
// by this class each step will have a specific ID, will have self status handling. each step will have a status of the status enum that is ready here
// and each step will left or entered by the work flow. 

class IWorkflowStep
{
public:
	// Each workflow step will be left by calling this method and it will set the status to finished or no changing from initializes or uninitialized
	virtual void LeaveWorkflowStep() = 0;

	// Each workflow that is available and initialized can be entered by workflow from this method.
	virtual void EnterWorkflowStep() = 0;

	// Each Step has a specific id that will be known by its id and this id will be set in constructor.
	virtual std::string GetStepId() const = 0;

	// Workflow Steps will be updated by this methods that is called by the workflow manager .
	virtual void UpdateStatus() = 0;
};