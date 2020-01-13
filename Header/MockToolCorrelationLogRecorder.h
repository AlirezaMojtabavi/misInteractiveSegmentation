#pragma once

#include "IToolCorrelationLogRecorder.h"

MOCK_BASE_CLASS(MockToolCorrelationLogRecorder, IToolCorrelationLogRecorder)
{
	MOCK_NON_CONST_METHOD(RecordLog, 4, 
		void (double timeInSeconds, const std::string& sourceTool, const std::string& destinationTool,
		std::shared_ptr<const ITransform> correlationTransform));
};