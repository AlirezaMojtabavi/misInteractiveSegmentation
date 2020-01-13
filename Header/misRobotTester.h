#pragma once
#include "serializable.h"
#include "misRobotCommandElement.h"
#include <deque>
#include "misBiopsyRobot.h"
#include "misElementKeeper.h"

//A class to test robot. This class makes a list of commands and keeps them in a std::deque<misElementKeeper>  m_CommandOrder and
// sends them to robot and gets responses from it.
//it has a misBiopsyRobot::Pointer  m_Robot which must be set before using this class (Nowhere in this class we New this pointer).
class misRobotTester:public  Serializable
{
private:
	std::deque<misElementKeeper>  m_CommandOrder;
	misBiopsyRobot*  m_Robot;

public:
	void AddCommand(misRobotCommandElement* element);
	void RunCommands();
	void SetRobot(misBiopsyRobot* val);
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
	misRobotTester(void);
	~misRobotTester(void);
};

