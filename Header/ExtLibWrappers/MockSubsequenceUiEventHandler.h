#pragma once

#include "ISubsequenceUiEventHandler.h"

namespace parcast
{

	MOCK_BASE_CLASS(MockSubsequenceUiEventHandler, ISubsequenceUiEventHandler)
	{
		MOCK_NON_CONST_METHOD(InvokeUiEvent, 1, void(const itk::EventObject &event));
		MOCK_NON_CONST_METHOD(SetAllStatesList, 1, void(const std::vector<std::string>& stateList));
		MOCK_NON_CONST_METHOD(SetSubSequenseStatusToUnderGoingTask, 3, void(std::string, misResultMessageEnums, std::string));
		MOCK_CONST_METHOD(GetSubTabName, 0, std::string());
		MOCK_CONST_METHOD(GetTabName, 0, std::string());
	};

}
