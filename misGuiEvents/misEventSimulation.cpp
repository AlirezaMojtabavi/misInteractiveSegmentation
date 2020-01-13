#include "StdAfx.h"
#include "misEventSimulation.h"

#include "misEventSerializer.h"
#include "misTryCatchDeserializationMACRO.h"

misEventSimulation::misEventSimulation(void)
{
	f.open("events.xml", std::ios::out);
	f<<"<EventSimulation>";
	f<<"<EventOrderList>";
}


misEventSimulation::~misEventSimulation(void)
{
	s.write(f);
	f<<"</EventOrderList>";
	f<<"</EventSimulation>";

	
	f.close();

}

void misEventSimulation::addEvent( misGUIEvent* event )
{
	misEventSerializer  sr(event,event->GetEventName());
	s.serialize("Event",sr);

}

std::vector<misEventSerializer> misEventSimulation::GetEvents()
{
	return m_EventOrderList;
}

void misEventSimulation::serialize( XmlSerializer& s ) const
{

}

void misEventSimulation::deserialize( XmlDeserializer& s )
{
	try
	{
		s.deserialize("EventOrderList",m_EventOrderList);


		
	}
	catch (...)
	{
		std::cout<<"failed in deserialize of misEventSimulation "<<std::endl;
	}
 
}



 