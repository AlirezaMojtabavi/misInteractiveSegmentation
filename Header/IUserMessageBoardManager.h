#pragma once

// The IUserMessageBoardManager class provides interface to objects capable of managing a typical message board. A message 
// board could be any user interface element that can display a single message with specific formatting options at any time. 
// The message board manager receives user messages from different sources, assigning unique IDs to each received message, 
// and stores them internally on a message stack. Then, based on the contents of the message stack, severity of each message, 
// sends the actual message to be displayed to the attached UI element. The formatting of the message is deduced from its 
// severity level. The same message ID can be used subsequently to remove the message from the board. The message will be 
// displayed on the board as long as it is not either removed or expired. Messages can be sent with a limited life-time 
// to have the board manager automatically remove them when they are expired. After a message is sent or removed, the actual
// message board is updated automatically - if necessary. At any time, the message to be displayed on the actual UI element
// is the message of the highest priority that is highest on the message stack.
class IUserMessageBoardManager
{
public:
	// Defines the severity level of each received message. Severity levels could affect how the message is displayed and also
	// help prioritize them on the stack.
	enum MessageSeverity
	{
		// Being of the highest priority on the message stack, MS_ERROR communicates an error message to the user.
		MS_ERROR,

		// Being of the second highest priority on the message stack, MS_WARNING communicates a warning message to the user.
		MS_WARNING,

		// Being of the lowest priority on the message stack, MS_INFO communicates a warning message to the user.
		MS_INFO
	};

	// The type of the ID's assigned to messages when sending them.
	typedef unsigned long long int MessageId;

	// Sends a message (pushes it on the message stack) specifying its text and severity, and optionally a life time (in 
	// milliseconds. Messages without a specified life time will not be removed from the stack unless explicitly requested 
	// through RemoveMessage(). The returned ID can be kept for subsequent removal of the message.
	virtual MessageId PushMessage(const std::string& message, MessageSeverity severity) = 0;
	virtual MessageId PushMessage(const std::string& message, MessageSeverity severity, double lifeTimeMs) = 0;

	// Removes a message previously sent using SendMessage() through the message ID received thereof. The messages will keep 
	// displaying unless they are expired or explicitly removed.
	virtual void RemoveMessage(MessageId messageIdToRemove) = 0;

	// Goes through the message stack, removing expired messages, and determines the message that must be presently displayed on
	// the board. Then it makes sure that the message is displayed on the UI element - by dispatching it to the UI if necessary.
	// It must be called in regular intervals to make sure that the expired messages are removed in time.
	virtual void UpdateState() = 0;

	virtual ~IUserMessageBoardManager(void)
	{
	}
};

