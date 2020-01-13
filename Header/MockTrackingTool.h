#pragma once

#include "ITrackingTool.h"

MOCK_BASE_CLASS(MockTrackingTool, ITrackingTool)
{
	// ICoordinateSystem:
	MOCK_CONST_METHOD(GetUID, 0, std::string ());
	MOCK_NON_CONST_METHOD(SetUID, 1, void(const std::string& )); // set a unique identifier string 
	// ITrackingTool:
	MOCK_CONST_METHOD(GetToolApplicationType, 0, misToolApplicationType ());
	MOCK_CONST_METHOD(GetTipValidationDistanceThreshold, 0, double ());
	MOCK_CONST_METHOD(GetTipCalibrationDistanceThreshold, 0, double ());
	MOCK_CONST_METHOD(GetOrientationCalibrationAngleThreshold, 0, double ());
	MOCK_CONST_METHOD(GetPositionFixationDistanceThreshold, 0, double ());
	MOCK_CONST_METHOD(GetOrientationFixationAngleThreshold, 0, double ());
	MOCK_CONST_METHOD(GetLastCalibrationTimeTag, 0, time_t ());
	MOCK_NON_CONST_METHOD(SetLastCalibrationTimeTag, 1, void (time_t timeTag));
	MOCK_CONST_METHOD(GetAxisStaticFeature, 0, std::shared_ptr<const ICoordinateSystem> ());
	MOCK_CONST_METHOD(GetAxisDynamicFeature, 0, std::shared_ptr<const ICoordinateSystem> ());
	MOCK_NON_CONST_METHOD(SetCalibrationTransform, 1, void (std::shared_ptr<const ITransform> transform));
	MOCK_CONST_METHOD(GetTipCalibrationViewCameraPosition, 0, const VectorType& ());
	MOCK_CONST_METHOD(GetOrientationCalibrationViewCameraPosition, 0, const VectorType& ());
	MOCK_CONST_METHOD(GetTipCalibrationViewCameraFocalPoint, 0, const VectorType& ());
	MOCK_CONST_METHOD(GetOrientationCalibrationViewCameraFocalPoint, 0, const VectorType& ());
	MOCK_CONST_METHOD(GetCalibrationFeature, 0, std::shared_ptr<const ICoordinateSystem> ());
	MOCK_CONST_METHOD(GetToolProperties, 0, const misToolProperties& ());
	MOCK_CONST_METHOD(GetTracker, 0, igstk::Tracker* ());
	MOCK_NON_CONST_METHOD(SetTracker, 1,  void (igstk::Tracker* ) );
	MOCK_CONST_METHOD(GetTrackerUID, 0, std::string());
	MOCK_CONST_METHOD(GetTrackedTool, 0, igstk::TrackerTool::Pointer ());
	MOCK_CONST_METHOD(GetTrackedToolExtraInformation, 0, ToolExtraInformation ());
	MOCK_CONST_METHOD(HasApplicationFlag, 1, bool (misToolProperties::ApplicationFlag flag));
	MOCK_CONST_METHOD(GetPatientUid, 0, std::string ());
	MOCK_NON_CONST_METHOD(SetPatientUid, 1, void (const std::string& patientUid));
	MOCK_NON_CONST_METHOD(SetToolStatus, 1, void (misToolStatus status));
	MOCK_NON_CONST_METHOD(ApplyToolCalibrationTransform,1, void (std::string currentPatientUid));
	MOCK_NON_CONST_METHOD(DetachFromTracker, 0,bool());
	MOCK_CONST_METHOD(GetToolName, 0,  std::string () );
	MOCK_NON_CONST_METHOD(SetDejitterizerHistoryLength, 1, void (int ) );
	MOCK_NON_CONST_METHOD(SetDejitterizerKernel, 1, void(const std::vector<double>& kernelCoefficients));
	MOCK_NON_CONST_METHOD(SetSmoothingDecider, 1, void(std::shared_ptr<IApplySmoothingDecider> ) );
	MOCK_CONST_METHOD(GetSmoothingDecider, 0, std::shared_ptr<IApplySmoothingDecider> ());
};