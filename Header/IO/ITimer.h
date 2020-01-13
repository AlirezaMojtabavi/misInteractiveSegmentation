#pragma once

// The ITimer class provides an abstract interface for measuring time. It features starting, stopping, resetting, and reading 
// current timer value (in seconds).
class ITimer
{
public:
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual void Reset() = 0;
	virtual double GetTime() const = 0;

	virtual ~ITimer() { };
};