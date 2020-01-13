#pragma once

#include "misLibraryMacroes.h"

class MISLIBRARYEXPORT  misLogToEventViewer
{
private:
	HANDLE m_LogHandle;

	static bool		instanceFlag;

	static misLogToEventViewer* s_LogWriter;

public:
	misLogToEventViewer(void);
	~misLogToEventViewer(void);
	static misLogToEventViewer* GetInstance();

	void WriteEntry(std::string  msg,PSID pSid);
	void WriteEntry(std::string  msg,WORD  eventType,PSID pSid);
};
