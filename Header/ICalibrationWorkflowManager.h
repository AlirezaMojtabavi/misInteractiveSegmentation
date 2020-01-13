#pragma once

#include "ITrackingTool.h"
#include "misCalibrationWorkflowManagerProperties.h"
#include "misTrackingManagerEnums.h"

// The ICalibrationWorkflowManager class provides the abstract interface for class(es) that manage MIS tracking tool calibration
// workflow. The client can set calibration workflow manager properties, the subject tracking tool, the calibration tracking tool,
// the tracker, and determine whether the process should be carried out automatically or manually.
// The whole process is carried out through repetative calls to UpdateStatus(). With each call, it makes calculations, based on the 
// current status of the calibration workflow manager, the tracking tools, the tracker, automatic/manual mode, and other specified
// properties, and then it either transits the calibration workflow manager to a new status or maintains the current status and
// performs other operations such as tracking data gathering, fixation analysis, setting calibration parameters on the tools ...
// The calibration workflow manager always starts in the ST_INITIAL state. On subsequent calls to UpdateStatus(), if the automatic
// calibration is enabled, it automatically transits to one of the IN_PROGRESS statuses. If the automatic calibration is not 
// enabled, status transition occurs only through calls to Start() and Reset(). In the manual mode, calling the start transits from
// idle statuses (ST_INITIAL, ST_TIP_VALIDATION_SUCCESSFUL, ST_TIP_CALIBRATION_DONE, ST_ORIENTATION_CALIBRATION_DONE) to the 
// IN_PROGRESS status of the next calibration activity in line. Specific succession of calibration activities is implementation 
// defined. Calling Reset() at any status clears internally gathered data and falls back to the last idle status.
// Finally, current status and progress of the calibration workflow manager can be examined through GetCurrentStatus() which 
// can be used by the supporting user interface, etc.
class ICalibrationWorkflowManager
{
public:
	// Orders the workflow manager to transit from the current
	// idle status to the next scheduled status. The exact order of state transitions is implementation defined.
	virtual void Start() = 0;

	// Resets internally kept calibration buffers and resets the current status of the workflow manager to the to ST_INITIAL, 
	// and reverts any changes made to the subject tool calibration data during since the workflow manager was last in the
	// ST_INITIAL status.
	virtual void Reset() = 0;

	// Resets internally kept calibration buffers and resets the current status of the workflow manager to the last idle status, 
	// and reverts any changes made to the subject tool calibration data since the workflow manager was in that status.
	virtual void ResetCurrentStep() = 0;

	// Asks the workflow manager to perform calibration operations (if in one of the IN_PROGRESS states) and update its status 
	// (if necessary). Also if automatic calibration is enabled, when the workflow manager is in an idle state, this will 
	// cause Start() to be called automatically. See GetCurrentStatus()
	virtual void UpdateStatus() = 0;

	// Gets the current status of the calibration workflow manager. A superordinate object can use this status to display 
	// appropriate messages to the user. 
	virtual misCalibrationWorkflowStatus GetCurrentStatus() const = 0;

	// Gets the amount of progress made within the current status provided that the workflow manager is in one of the IN_PROGRESS
	// statuses. It returns zero when the workflow manager is in one of the idle statuses.
	virtual double GetCurrentStateProgress() const = 0;

	// Sets/gets the subject tracking tool. The calibration process involves gathering of data from the subject tool and comparing 
	// it with data from the calibration tool and finally the calibration adjustments are applied to the subject tool. 
	// See SetCalibrationTrackingTool().
	virtual void SetSubjectTrackingTool( std::shared_ptr<ITrackingTool> trackingTool ) = 0;
	virtual std::shared_ptr<const ITrackingTool> GetSubjectTrackingTool() const = 0;

	// Sets/gets the calibration tool whose spatial position and orientation are previously known and therefore can be used for 
	// calibrating other subject tools. See SetSubjectTrackingTool().
	virtual void SetCalibrationTrackingTool(std::shared_ptr<const ITrackingTool> trackingTool ) = 0;
	virtual std::shared_ptr<const ITrackingTool> GetCalibrationTrackingTool() const = 0;

	// Tells the workflow manager whether calls to UpdateStatus() should automatically transit through workflow statuses as the
	// calibration process is proceeded with, or the current status should only be changed through explicit calls to 
	// Start() and Reset(). See Start(), Reset()
	virtual void SetAutomaticCalibration(bool isEnabled) = 0;
	virtual bool GetAutomaticCalibration() const = 0;

	// Sets/gets the properties governing overall behavior of the calibration workflow manager.
	virtual void SetProperties(const misCalibrationWorkflowManagerProperties& tracker) = 0;
	virtual const misCalibrationWorkflowManagerProperties& GetProperties() const = 0;

	virtual ~ICalibrationWorkflowManager(void)
	{
	}
};

