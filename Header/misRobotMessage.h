#pragma once
#include "misRobotCommandElement.h"
#include <string>
class misRobotMessage:public misRobotCommandElement
{
private:
	std::string  m_ReadMessage;
public:
	misRobotMessage(std::string message);
	misRobotMessage();
	void SetMessage(std::string message);
	~misRobotMessage(void);
	virtual std::string ToString();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
	virtual std::string GetClassType();
};
