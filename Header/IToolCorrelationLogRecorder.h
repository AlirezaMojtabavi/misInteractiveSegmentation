#pragma once

// The IToolCorrelationLogRecorder class provides an interface to classes that record correlation between two tracker tools.
// It sports a RecordLog method that registers a single log record to a backend log destination.
class IToolCorrelationLogRecorder
{
public:
	// Appends a single log record based on the provided information to the backend log destination.
	virtual void RecordLog(double timeInSeconds, const std::string& sourceTool, const std::string& destinationTool,
		std::shared_ptr<const ITransform> correlationTransform) = 0;

	virtual ~IToolCorrelationLogRecorder() { };
};