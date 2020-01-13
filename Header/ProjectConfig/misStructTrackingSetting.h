#pragma once

#include "misCalibrationWorkflowManagerProperties.h"
#include "misMicronTrackerSetting.h"
#include "misTimePassingForActionPropertiesStr.h"
#include "misTrackingManagerEnums.h"
#include "misTrackingManagerTypes.h"


struct misStructTrackingSetting : public Serializable
{
public:
	int						 m_MicronFrequncy;
	bool                     m_LoadDafaultTools;
	bool                     AnalyzeAndShowToolPositionData;
	misStrctSettingPolaris   m_SettingPolaris;
	misMicronTrackerSetting  m_MicronSetting;
	
	misCalibrationWorkflowManagerProperties m_CalibrationWorkflowManagerProperties;

	// Time, in milliseconds, to wait after automatic calibration/validation process is completed before the tool accuracy 
	// window is automatically closed.
	double m_TimeWatingToCloseAfterCalibrationDone;

	// Time, in milliseconds, to wait after detecting a new tracking tool before the tool accuracy window is displayed (if 
	// the tool is still visible after that time).
	double m_TimeWaitingBeforeCalibrationStart;

	// The factor by which to increase the WaitingTimeBeforeCalibrationStarts parameter for a tracking tool each time the 
	// user cancels the calibration popup screen.
	double m_PreCalibrationWaitTimeGrowthFactor;

	//misSimpleToolNameListTypdef		m_AllTools;
	//misSimpleToolNameListTypdef		m_AllUploadedTools;
	std::vector<std::string>		m_UploadedTools;
	TrackerType						m_TypeOfTracker;//added by -M.A-

	// Time, in seconds, that a calibrated tool is considered valid and is not recalibrated even if the application is 
	// restarted and the tool is detected again. It acts based on the last calibration time tag of each tracking tool.
	double m_ToolCalibrationValidityPeriod;

	misToolNameIDMapTypedef			m_ToolNameIDMap;

	// Threshold for the rate of failed communication attempts within the last evaluation period. A failure rate above this 
	// threshold will cause reporting a disconnected state. The threshold is in the range [0..1].
	double m_TrackerCommunicationFailureRateThreshold;
	
	// Amount of time, in seconds, during which tracker connectivity is observed and failure rate is compared with the threshold.
	double m_MicronTrackerConnectivityEvaluationDuration;
	double m_PolarisTrackerConnectivityEvaluationDuration;

	double m_TimeBeforeReconnecting = 3000;// in miliseconds
	double m_NumberOfTrialsForMicronConnecting = 10;// in miliseconds
	double m_NumberOfTrialsForPolarisConnecting = 10;// in miliseconds
	misStructTrackingSetting();

	void Reset();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
};
