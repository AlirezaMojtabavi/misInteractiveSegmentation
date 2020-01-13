#pragma once

// The IStatusLogger provides an interface that enables periodical evaluation and logging of certain status parameters. The
// status parameters, output logging format and the log destination is up to the implementation. UpdateLogs must be called
// periodically to ensure the logs are appended when necessary. 
class IStatusLogger
{
public:
	// Evaluate current status parameters (query a source, etc.), generate a new log record if necessary, and append it to 
	// the log destination.
	virtual void UpdateLogs() = 0;

	// Stop and start enable and disable evaluation of status parameters whenever UpdateLogs is called. Therefore calling 
	// UpdateLogs when the logger is in the Stopped state has no effect.
	virtual void Stop() = 0;
	virtual void Start() = 0;
	virtual bool IsStarted() const = 0;

	virtual ~IStatusLogger() { };
};