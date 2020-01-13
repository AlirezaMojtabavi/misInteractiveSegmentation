#pragma once

#include "ITrackingToolQuery.h"

MOCK_BASE_CLASS(MockTrackingToolQuery, ITrackingToolQuery)
{
	MOCK_CONST_METHOD(ByApplicationFlag, 1, std::shared_ptr<ITrackingTool> (misToolProperties::ApplicationFlag flag));
	MOCK_CONST_METHOD(ByPartNumber, 1, std::shared_ptr<ITrackingTool> (const std::string& partNumber));
	MOCK_CONST_METHOD(ByToolName, 1, std::shared_ptr<ITrackingTool> (const std::string& toolName));
	MOCK_CONST_METHOD(ByUid, 1, std::shared_ptr<ITrackingTool> ByUid(const std::string& uid));
	MOCK_CONST_METHOD(GetAllVisibleCalibratedNavigationTools, 0, std::vector<std::shared_ptr<ITrackingTool>>());
	MOCK_CONST_METHOD(GetAllVisibleCalibrationTools, 0, std::vector<std::shared_ptr<ITrackingTool>>());
};