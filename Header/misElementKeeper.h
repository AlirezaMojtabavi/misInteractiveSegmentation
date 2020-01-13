#include "serializable.h"
#include "misRobotCommandElement.h"
#include "xmldeserializer.h"
#include "xmlserializer.h"

class misElementKeeper:public  Serializable
{
private:
	std::string m_type;
	misRobotCommandElement*  m_element;

public:
	misElementKeeper(misRobotCommandElement* elemnt,std::string  type);
	misElementKeeper();
	misRobotCommandElement* GetElement();
	std::string GetType();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
};