#pragma once

#include "misEventSerializer.h"
#include "misGuiEvent.h"

class misEventSimulation:public Serializable
{
private:
		std::vector<misEventSerializer>  m_EventOrderList;
		std::ofstream f;
			XmlSerializer s;
public:

	void addEvent(misGUIEvent*  event);
	std::vector<misEventSerializer> GetEvents();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
	misEventSimulation(void);
	~misEventSimulation(void);
};
