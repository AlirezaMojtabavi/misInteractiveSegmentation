#pragma once
#include "IUserMessageBoardManager.h"

#include <string>

// The GuiBoardMessage structure serves as the payload to the events sent to GUI which request displaying a message on the
// user message board.
struct GuiBoardMessage 
{
	std::string m_MessageText;

	// Severity of the message determines its formatting and appearance rendered by the GUI.
	IUserMessageBoardManager::MessageSeverity m_MessageSeverity;	

	GuiBoardMessage()
	{
		m_MessageText = "";
		m_MessageSeverity = IUserMessageBoardManager::MS_INFO;
	}
};