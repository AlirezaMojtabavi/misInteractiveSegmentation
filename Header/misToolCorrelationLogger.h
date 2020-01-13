#pragma once

#include "ICoordinateSystemCorrelationManager.h"
#include "IStatusLogger.h"
#include "ITextFileWriter.h"
#include "ITimer.h"
#include "ITrackingToolQuery.h"
#include "IToolCorrelationLogRecorder.h"

class misToolCorrelationLogger : public IStatusLogger
{
public:
	misToolCorrelationLogger(std::shared_ptr<ITrackingToolQuery> toolQuery, 
		std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > correlationManager,
		std::shared_ptr<ITimer> timer, std::shared_ptr<IToolCorrelationLogRecorder> logRecorder);

	// Specifies a pair of tools (identified by part numbers), the correlation between which (from source to destination) should
	// be logged.
	void AddToolPair(const std::string& sourceTrackerToolPartNumber, const std::string& destinationTrackerToolPartNumber);

	// Set the length of time, in seconds, between sequential log records.
	void SetTimeInterval(double interval);

	virtual void UpdateLogs() override;
	virtual void Stop() override;
	virtual void Start() override;
	virtual bool IsStarted() const override;
private:
	typedef std::pair<std::string, std::string> CoordSysPair;

	std::shared_ptr<ITrackingToolQuery> m_TrackingToolQuery;
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CorrelationManager;
	std::shared_ptr<ITimer> m_Timer;
	std::shared_ptr<IToolCorrelationLogRecorder> m_LogRecorder;

	std::vector<CoordSysPair> m_CoordSysPairs;
	std::map<std::string, std::string> m_CoordSysUidToToolPartName;
	double m_TimeInterval;
	double m_LastRecordTime;
	bool m_IsRunning;
};