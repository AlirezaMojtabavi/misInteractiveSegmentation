#pragma once

#include "ITrackingToolRepository.h"

MOCK_BASE_CLASS(MockTrackingToolRepository, ITrackingToolRepository)
{
	MOCK_NON_CONST_METHOD(AddTool, 1, void (std::shared_ptr<ITrackingTool> newTool));
	MOCK_NON_CONST_METHOD(RemoveTool, 1, void (std::shared_ptr<ITrackingTool> newTool));
	MOCK_NON_CONST_METHOD(RemoveAllTools, 0, void ());
	MOCK_CONST_METHOD(GetAllTools, 0, TrackerToolListType ());
};