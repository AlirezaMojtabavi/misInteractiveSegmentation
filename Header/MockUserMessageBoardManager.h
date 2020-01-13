#pragma once

#include <turtle/mock.hpp>

#include "IUserMessageBoardManager.h"

MOCK_BASE_CLASS(MockUserMessageBoardManager, IUserMessageBoardManager)
{
	MOCK_NON_CONST_METHOD(SendMessage, 2, MessageId (const std::string& message, MessageSeverity severity));
	MOCK_NON_CONST_METHOD(SendMessage, 3, MessageId (const std::string& message, MessageSeverity severity, double lifeTimeMs));
	MOCK_NON_CONST_METHOD(RemoveMessage, 1, void (MessageId messageIdToRemove));
	MOCK_NON_CONST_METHOD(UpdateState, 0, void ());
};