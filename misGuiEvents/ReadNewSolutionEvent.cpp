#include "StdAfx.h"
#include "ReadNewSolutionEvent.h"

using namespace std;

ReadNewSolutionEvent::ReadNewSolutionEvent( const Self&s ) :misGUIEvent(s)
{

}

ReadNewSolutionEvent::ReadNewSolutionEvent()
{

}

ReadNewSolutionEvent::~ReadNewSolutionEvent(void)
{
}

 

char * ReadNewSolutionEvent::GetEventName()
{
	return "ReadNewSolutionEvent";
}

void ReadNewSolutionEvent::Set( const string & _var )
{
	m_Payload = _var;
}

const string & ReadNewSolutionEvent::Get() const
{
	return m_Payload;
}

void ReadNewSolutionEvent::serialize( XmlSerializer& s ) const
{
	misGUIEvent::serialize(s);
	s.serialize("Payload", m_Payload);
}

void ReadNewSolutionEvent::deserialize( XmlDeserializer& s )
{
	misGUIEvent::deserialize(s);
	s.deserialize("Payload", m_Payload);

}
