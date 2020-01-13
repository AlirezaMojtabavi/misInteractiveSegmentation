#pragma once

#include "misToolProperties.h"
#include "serializable.h"

struct  misStrctComConnectionOptions:public Serializable
{
	int ComPort;
	int BaudRate;
	int DataBit;
	int StopBit;
	int Parity;
	int HandShake;
	//string m_TypeOfTracker;
	misToolPropertiesListTypdef ToolList;
	misStrctComConnectionOptions();

	virtual void serialize(XmlSerializer& s) const;
    virtual void deserialize(XmlDeserializer& s);
};
