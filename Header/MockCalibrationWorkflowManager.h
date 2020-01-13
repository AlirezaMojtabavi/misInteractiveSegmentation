#pragma once

#include <boost/test/auto_unit_test.hpp>
#include <turtle/mock.hpp>

#include "ICalibrationWorkflowManager.h"

MOCK_BASE_CLASS(MockCalibrationWorkflowManager, ICalibrationWorkflowManager)
{
	MOCK_NON_CONST_METHOD(Start, 0, void());
	MOCK_NON_CONST_METHOD(Reset, 0, void());
	MOCK_NON_CONST_METHOD(ResetCurrentStep, 0, void());
	MOCK_NON_CONST_METHOD(UpdateStatus, 0, void());
	MOCK_CONST_METHOD(GetCurrentStatus, 0, misCalibrationWorkflowStatus());
	MOCK_CONST_METHOD(GetCurrentStateProgress, 0, double());
	MOCK_NON_CONST_METHOD(SetSubjectTrackingTool, 1, void(std::shared_ptr<INavigationTrackingTool>));
	MOCK_CONST_METHOD(GetSubjectTrackingTool, 0, std::shared_ptr<const INavigationTrackingTool> ());
	MOCK_NON_CONST_METHOD(SetCalibrationTrackingTool, 1, void(std::shared_ptr<const ICalibrationTrackingTool>));
	MOCK_CONST_METHOD(GetCalibrationTrackingTool, 0, std::shared_ptr<const ICalibrationTrackingTool> ());
	MOCK_NON_CONST_METHOD(SetTracker, 1, void(igstk::Tracker*));
	MOCK_CONST_METHOD(GetTracker, 0, igstk::Tracker* ());
	MOCK_NON_CONST_METHOD(SetAutomaticCalibration, 1, void(bool));
	MOCK_CONST_METHOD(GetAutomaticCalibration, 0, bool());
	MOCK_NON_CONST_METHOD(SetProperties, 1, void(const misCalibrationWorkflowManagerProperties&));
	MOCK_CONST_METHOD(GetProperties, 0, const misCalibrationWorkflowManagerProperties&());
};