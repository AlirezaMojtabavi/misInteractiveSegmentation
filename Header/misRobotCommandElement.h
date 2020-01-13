#pragma once
#include <string>
class misRobotCommandElement:public Serializable
{
private:

public:

	virtual std::string ToString()=0;
 	virtual std::string GetClassType()=0;
};
