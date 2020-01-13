#pragma once

class MicronTrackerExceptions
{
protected:
	std::string m_ExceptionMessage;

	//code of exception from 0 to 70 (Refer to void MicronTracker::CreateErrorCodeList())
	mtCompletionCode m_ExceptionCode;

	MicronTrackerExceptions(void)
	{
		m_ExceptionCode = mtInternalMTError;
		m_ExceptionMessage = "";
	}

public:
	MicronTrackerExceptions(std::string CurrentMessage, mtCompletionCode CurrentExceptionCode);
	MicronTrackerExceptions::MicronTrackerExceptions(std::string CurrentMessage);
	~MicronTrackerExceptions(void);
	
	void SetMessage(std::string CurrentMessage, mtCompletionCode CurrentExceptionCode);
	void SetMessage(std::string CurrentMessage);
	std::string GetMicronExceptionMessage();
	mtCompletionCode GetExceptionCode();
};

