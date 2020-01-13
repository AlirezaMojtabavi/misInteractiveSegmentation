#pragma once
#include "misRobotCommandElement.h"
class misTextCommand:public misRobotCommandElement
{
private:
	std::string m_Command;
public:
	virtual std::string ToString();
	misTextCommand(std::string command);
	void SetCommand(std::string command);
	misTextCommand();
	~misTextCommand(void);
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
	virtual std::string GetClassType();
};
