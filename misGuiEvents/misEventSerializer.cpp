#include "stdafx.h"
#include "misEventSerializer.h"

#include "misGUIEventFactory.h"
#include "misGuiEvent.h"

misEventSerializer::misEventSerializer( void )
{

}

misEventSerializer::misEventSerializer( misGUIEvent* elemnt,std::string type )
{
	m_type=type;
	m_element=elemnt;
}

misEventSerializer::~misEventSerializer( void )
{

}

void misEventSerializer::serialize( XmlSerializer& s ) const
{
	try
	{
		s.serialize("type", m_type);
		s.serialize("element",*m_element);
	}
	catch (...)
	{
		std::cout<<"failed in serialize of misEventSerializer"<<std::endl;
	}
}

void misEventSerializer::deserialize( XmlDeserializer& s )
{
	try
	{
		s.deserialize("type", m_type);


		m_element=misGUIEventFactory::CreateElement(m_type);
		if (!m_element)
		{
			std::cout<<"factory not founed:"<<m_type<<std::endl ;
			return;
		}
		//_ASSERT(m_element!=NULL);
		s.deserialize("element",*m_element);
	}
	catch (...)
	{
		std::cout<<"failed in deserialize of misTextCommand"<<std::endl;
	}
}

std::string misEventSerializer::GetType()
{
	return m_type;
}

misGUIEvent* misEventSerializer::GetElement()
{
	return m_element;
}
