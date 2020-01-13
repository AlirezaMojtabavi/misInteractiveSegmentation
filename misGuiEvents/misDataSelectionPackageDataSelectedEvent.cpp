#include "StdAfx.h"
#include "misDataSelectionPackageDataSelectedEvent.h"

using namespace std;

misDataSelectionPackageDataSelectedEvent::misDataSelectionPackageDataSelectedEvent( const Self&s ) :misGUIEvent(s)
{

}

misDataSelectionPackageDataSelectedEvent::misDataSelectionPackageDataSelectedEvent()
{

}

misDataSelectionPackageDataSelectedEvent::~misDataSelectionPackageDataSelectedEvent(void)
{
}



char * misDataSelectionPackageDataSelectedEvent::GetEventName()
{
	return "misDataSelectionPackageDataSelectedEvent";
}

void misDataSelectionPackageDataSelectedEvent::Set( const string & _var )
{
	m_Payload = _var;
}

const string & misDataSelectionPackageDataSelectedEvent::Get() const
{
	return m_Payload;
}

void misDataSelectionPackageDataSelectedEvent::serialize( XmlSerializer& s ) const
{
	misGUIEvent::serialize(s);
	s.serialize("Payload", m_Payload);
}

void misDataSelectionPackageDataSelectedEvent::deserialize( XmlDeserializer& s )
{
	misGUIEvent::deserialize(s);
	s.deserialize("Payload", m_Payload);

}
