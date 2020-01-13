#pragma once

#include "IUserMessageBoardManager.h"
#include "misLibraryMacroes.h"

// The misUserMessageBoardManager class implements the IUserMessageBoardManager interface. It communicates messages to the 
// actual UI element through a function which it receives during construction.
class MISLIBRARYEXPORT misUserMessageBoardManager : public IUserMessageBoardManager
{
public:
	// Type of the function to use for communicating messages to the actual UI element.
	typedef std::function<void (const std::string& message, MessageSeverity severity)> DisplayMessageFunction;

	misUserMessageBoardManager(DisplayMessageFunction actualMessageBoardDisplayFunction);

	// IUserMessageBoardManager interface:
	MessageId PushMessage( const std::string& message, MessageSeverity severity ) override;
	MessageId PushMessage( const std::string& message, MessageSeverity severity, double lifeTimeMs ) override;
	void RemoveMessage( MessageId messageIdToRemove ) override;
	void UpdateState();

private:
	typedef boost::chrono::steady_clock ClockType;

	// The MessageDescriptor structure is used to store each individual message along with its properties in the stack.
	struct MessageDescriptor
	{
		MessageId m_MessageId;
		std::string m_MessageText;
		MessageSeverity m_Severity;
		bool m_IsTimeLimited;	// Determines whether a limited life time has been specified for the message.
		
		//	Time when the message has been sent (used to calculate expiration time of the message
		ClockType::time_point m_SentTime;

		double m_LifeTime;
	};

	// Generates a new unique ID to be assigned to a message being store.
	MessageId GenerateNewId();

	std::list<MessageDescriptor> m_MessageStack;

	// ID of the message currently being displayed on the UI element (last message sent to UI). Kept in order to know whether 
	// sending message to UI is necessary after each modification to the message stack.
	MessageId m_CurrentMessageId;

	// The function pointer used for communicating messages to the front end UI element.
	DisplayMessageFunction m_SendMessageToUi;

	// Last generated ID using GenerateNewId(). It is used by the same method for generating the next ID.
	MessageId m_LastGeneratedId;
};