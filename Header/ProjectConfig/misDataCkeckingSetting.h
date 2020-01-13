#pragma once
#include "serializable.h"

struct misDataCkeckingSetting:public Serializable
{
	bool LoggerEnabled;
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
};
