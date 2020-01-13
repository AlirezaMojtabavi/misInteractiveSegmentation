#pragma once
#include "igstkCommunication.h"

// The ITrackerConnectivity class provides an abstract interface using which tracker connectivity can be examined at each time.
// It reports the connected state provided that rate of failing communication results in a specified duration of time is 
// smaller than a certain threshold. To test tracker connectivity, every communication result with the tracker must be pushed 
// immediately.
class ITrackerConnectivity
{
public: 
	virtual ~ITrackerConnectivity() { }	// Default virtual destructor necessary for abstract classes.

	// Performs the check if required and determines if the tracker connectivity is acceptable.
	virtual bool TrackerIsConnected() = 0; 

	// Push the result from the last performed communication with the tracker.
	virtual void PushTrackerCommunicationResult(igstk::Communication::ResultType communicationResult) = 0;

	// Amount of time, in seconds, during which tracker connectivity is observed and failure rate is compared with the threshold.
	virtual void SetEvaluationDuration(double durationSecs) = 0;

	// The time, from then tracker connectivity is observed.
	virtual void SetStartTime(time_t startTime) = 0;

	// Threshold for the rate of failed communication attempts within the last evaluation period. A failure rate above this 
	// threshold will cause reporting a disconnected state. The threshold is in the range [0..1].
	virtual void SetFailureRateThreshold(double threshold) = 0;
};