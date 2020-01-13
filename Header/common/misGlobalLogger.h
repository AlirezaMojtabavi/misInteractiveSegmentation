#pragma once

#include "logmanager.h"

class  misGlobalLogger : public TextLog
{
private:
	//static bool m_created;

	misGlobalLogger(const std::string &filename, bool WriteDateStampingInLogFile = true,
		bool WriteTimeStampingInLogFile= true,
		bool WriteCategoryInLogFile = true, 
		bool WriteLogLevelInLogFile = true);
	~misGlobalLogger(void);

public:

	static misGlobalLogger * GetInstance(const std::string &filename, bool WriteDateStampingInLogFile = true,
										bool WriteTimeStampingInLogFile= true,
										bool WriteCategoryInLogFile = true, 
										bool WriteLogLevelInLogFile = true);
	
	//void log(const std::string &cat, LogLevel level, const std::string &msg, const std::string &extendedInfo);
};

//#define WRITE_LOG_INFORMATION(Catrgory,LevelOfLog,Log_Message, Extra_Info)\
//{\
//	if(m_LoggerForRecalibrationTest)\
//{\
//	m_LoggerForRecalibrationTest->log(Catrgory,LevelOfLog,Log_Message,Extra_Info);\
//}\
//}\
//
