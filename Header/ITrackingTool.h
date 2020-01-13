#pragma once

#include "ICoordinateSystem.h"
#include "ITransform.h"
#include "misToolProperties.h"
#include "misToolTypeEnum.h"
#include <igstkTracker.h>
#include "IAppySmoothingDecider.h"

// The ITrackingTool class provides the abstract interface to classes that represent tracking tools and provide services such as
// tool positioning and orientation as well as tracking tool type.
class ITrackingTool : public ICoordinateSystem
{
public:
	typedef itk::Vector<double> VectorType;

	// The following points, all in local tracking tool coordinates, determine how the calibration process using the calibration
	// tool is best visualized (in terms of informativeness). The points define rendering camera configuration. Different 
	// camera configurations are desirable for the orientation calibration than are for tip calibration/validation. The camera
	// configuration in each case includes a camera position and a camera focal point.
	virtual const VectorType& GetTipCalibrationViewCameraPosition() const = 0;
	virtual const VectorType& GetOrientationCalibrationViewCameraPosition() const = 0;
	virtual const VectorType& GetTipCalibrationViewCameraFocalPoint() const = 0;
	virtual const VectorType& GetOrientationCalibrationViewCameraFocalPoint() const = 0;

	// Gets an ICoordinateSystem which specifies calibration point (used to calculate tip offset of a subject tool)
	virtual std::shared_ptr<const ICoordinateSystem> GetCalibrationFeature() const = 0;

	// Maximum amount of deviation that the position of subject tracking tool tip is allowed demonstrate during tool validation.
	virtual double GetTipValidationDistanceThreshold() const = 0;

	// Maximum amount of deviation that the position of subject tracking tool tip is allowed demonstrate during tool calibration
	// from the original position set for the tool. Values as high as 50cm are justified as detached tools demonstrate great 
	// deviations from original tool tip position.
	virtual double GetTipCalibrationDistanceThreshold() const = 0;

	// Maximum amount of deviation angle (in degrees) that the orientation of the subject tracking tool is allowed to demonstrate 
	// during tool calibration from the original orientation set for the tool. When setting this value, detachable tools must also
	// be considered (with possibly great amounts of deviation).
	virtual double GetOrientationCalibrationAngleThreshold() const = 0;

	// Maximum amount of deviation (in millimetres) that the position of subject tracking tool tip is allowed to demonstrate 
	// during fixation analysis in order to be considered "roughly" fixed.
	virtual double GetPositionFixationDistanceThreshold() const = 0;

	// Maximum amount of angular deviation (in degrees) that the orientation of the subject tracking tool is allowed to 
	// demonstrate during fixation analysis in order to be considered "roughly" fixed.
	virtual double GetOrientationFixationAngleThreshold() const = 0;

	virtual time_t GetLastCalibrationTimeTag() const = 0;
	virtual void SetLastCalibrationTimeTag(time_t timeTag) = 0;

	virtual std::string GetPatientUid() const = 0;
	virtual void SetPatientUid(const std::string& patientUid) = 0;

	virtual std::shared_ptr<const ICoordinateSystem> GetAxisStaticFeature() const = 0;
	virtual std::shared_ptr<const ICoordinateSystem> GetAxisDynamicFeature() const = 0;

	// Sets the calibration transform, that transforms a point or vector from the tool dynamic axis coordinate system to the 
	// coordinate system of the tool. Set NULL to remove or invalidate current calibration.
	virtual void SetCalibrationTransform(std::shared_ptr<const ITransform> transform) = 0;

	virtual const misToolProperties& GetToolProperties() const = 0;
	virtual igstk::Tracker* GetTracker() const = 0;
	virtual std::string GetTrackerUID() const = 0;
	virtual void SetTracker(igstk::Tracker* tracker) = 0;
	virtual igstk::TrackerTool::Pointer GetTrackedTool() const = 0;
	virtual ToolExtraInformation GetTrackedToolExtraInformation() const = 0;

	virtual void SetToolStatus(misToolStatus status) = 0;

	// Determines whether the tracking tool has the specified flag set as part of its construction properties.
	virtual bool HasApplicationFlag(misToolProperties::ApplicationFlag flag) const = 0;
	virtual void ApplyToolCalibrationTransform(std::string currentPatientUid) = 0;
	virtual bool DetachFromTracker() = 0;
	virtual std::string GetToolName() const = 0;
	virtual void SetDejitterizerHistoryLength(int historyLength) = 0;
	virtual void SetDejitterizerKernel(const std::vector<double>& kernelCoefficients) = 0;
	virtual void SetSmoothingDecider(std::shared_ptr<IApplySmoothingDecider> val) = 0;
	virtual std::shared_ptr<IApplySmoothingDecider> GetSmoothingDecider() const = 0;
	virtual ~ITrackingTool() = default;
};