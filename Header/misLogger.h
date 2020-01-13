#ifndef _MISLOGGER_
#define _MISLOGGER_

#pragma once

#include "NativeLogMessageBoxData.h"
#include "misEnums.h"
#include "misEvent.h"
#include "misLibraryMacroes.h"
#include "itkMutexLock.h"

#pragma warning ( push )
#pragma warning ( disable : 4800 )
igstkLoadedEventMacro(misLogMessageBoxEvent, misEvent,NativeLogMessageBoxData);
#pragma warning ( pop )


//======================================================================================================
/// a class  to add filtering  to igstk::logger
//
class   MISLIBRARYEXPORT misLogger :public igstk::Logger
{
private:

	bool  m_Enable;


	itk::LoggerBase::PriorityLevelType m_CurrentLevel;
	std::vector<std::string> m_LevelString ;
public:
	
	bool GetEnable() const { return m_Enable; }
	void SetEnable(bool val) { m_Enable = val; }


	misLogger& operator<<(std::string msg); 
	misLogger& operator<<(char*  str) ;
	misLogger& operator<<(double value); 
	misLogger& operator<<(int value) ;
	misLogger& operator<<(bool  value); 
	misLogger& operator<<(size_t value); 
	
	void  LogValue(double  valueLog);
	int LogMemoryUsedInProcess(std::string whereFunction);
	std::string BuildFormattedEntry(PriorityLevelType level, std::string const & content);

	//string m_classList;
	//itkNewMacro(Self);

public:
	virtual void Write(LoggerBase::PriorityLevelType level, std::string const & content);
public:
	~misLogger(void);
	void SetWritingLevel(itk::LoggerBase::PriorityLevelType val);
	static  misLogger*  GetInstance();
	static  itk::SimpleMutexLock  g_Mutext;
protected:

	misLogger(void);
	PSID	GetUserSid();
	itk::LoggerBase::PriorityLevelType ToEnum(std::string enumstring);
};

#define  MisLog(text)\
	if(m_Logger) 	(*m_Logger)<<text;

#endif
