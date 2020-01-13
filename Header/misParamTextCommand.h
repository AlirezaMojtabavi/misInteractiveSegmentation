#pragma once
#include "misRobotCommandElement.h"
class misParamTextCommand:public misRobotCommandElement
{
private:
	std::string  m_Command;
	double       m_CommandValue;

public:

	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
	misParamTextCommand(std::string command,double       commandValue);
	virtual std::string ToString();
	~misParamTextCommand(void);
};
