#pragma once

class ITrackingTool;

namespace parcast
{
	// The CalibrationProfile enum values determine the sequence of the states that the workflow executes. 
	enum CalibrationProfile
	{
		// ST_INITIAL -> ST_TIP_CALIBRATION_IN_PROGRESS -> ST_TIP_CALIBRATION_DONE -> ST_ORIENTATION_CALIBRATION_DONE
		CP_COMPLETE,

		// ST_INITIAL -> ST_TIP_VALIDATION_IN_PROGRESS -> (ST_TIP_VALIDATION_SUCCESSFUL or ST_TIP_VALIDATION_FAILED)
		CP_PARTIAL
	};

	class ICalibrationProfileFinder
	{
	public:
		virtual CalibrationProfile Get() const = 0;
		virtual void SetUserType(const std::string& userType) = 0;
		virtual void SetSubjectTrackingTool(std::shared_ptr<ITrackingTool> trackingTool) = 0;
	};
}

