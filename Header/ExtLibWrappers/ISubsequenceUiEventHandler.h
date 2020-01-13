#pragma once

#include "misResultMessageEnums.h"

namespace itk
{
	class itk::EventObject;
}

namespace parcast
{

	class ISubsequenceUiEventHandler
	{
	public:
		virtual ~ISubsequenceUiEventHandler() = default;

		virtual void InvokeUiEvent(const itk::EventObject &event) = 0;
		virtual void SetAllStatesList(const std::vector<std::string>& stateList) = 0;
		virtual void SetSubSequenseStatusToUnderGoingTask(
			std::string state, misResultMessageEnums resultType, std::string resultDescrpition) = 0;
		virtual std::string GetSubTabName() const = 0;
		virtual std::string GetTabName() const = 0;
	};

}