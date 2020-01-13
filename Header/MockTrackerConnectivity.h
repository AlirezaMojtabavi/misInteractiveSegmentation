#pragma once

#include <turtle/mock.hpp>

#include "ITrackerConnectivity.h"

MOCK_BASE_CLASS(MockTrackerConnectivity, ITrackerConnectivity)
{
	MOCK_NON_CONST_METHOD(TrackerIsConnected, 0, bool ());
	MOCK_NON_CONST_METHOD(PushTrackerCommunicationResult, 1, void (igstk::Communication::ResultType communicationResult));
	MOCK_NON_CONST_METHOD(SetEvaluationDuration, 1, void (double durationSecs));
	MOCK_NON_CONST_METHOD(SetStartTime, 1, void (time_t startTime));
	MOCK_NON_CONST_METHOD(SetFailureRateThreshold, 1, void (double threshold));
};