#pragma once

#include "ITrackerConnectivity.h"

// 
class misTrackerConnectivity :	public ITrackerConnectivity
{
public:
	misTrackerConnectivity(void);
	~misTrackerConnectivity(void);

	virtual bool TrackerIsConnected() override;  
	virtual void PushTrackerCommunicationResult(igstk::Communication::ResultType communicationResult) override;
	virtual void SetEvaluationDuration(double durationSecs) override;
	virtual void SetStartTime(time_t startTime) override;
	virtual void SetFailureRateThreshold( double threshold ) override;

private:
	std::stack<igstk::Communication::ResultType> m_CommunicationResult;
	double m_EvaluationDuration;
	double m_FailureRateThreshold;
	time_t m_StartTime;
};

