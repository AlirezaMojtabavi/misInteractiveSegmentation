#pragma once

#include "misLibraryMacroes.h"
#include "misLogger.h"

class  MISLIBRARYEXPORT misLoggerManager
{
private:

	misLogger*              m_Logger;
	void AddConsloOutput();
	void AddFileOutput();
	  void InitializeLigger();
public:
	misLogger* GetLogger() const;
	std::string GetCurrentTimeStr() const;

	misLoggerManager(void);
	~misLoggerManager(void);
};
