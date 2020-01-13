#pragma once
#include <misResultMessageEnums.h>

class IApplySubSegStatesEventToGUI
{
public:
	virtual ~IApplySubSegStatesEventToGUI() = default;
 
	virtual void SendUpdateGUIStateToGUI(std::string state, misResultMessageEnums resultType,
		std::string resultDescription) = 0;
}; 