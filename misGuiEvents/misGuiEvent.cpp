#include "stdafx.h"
#include "misGuiEvent.h"

using namespace std;

void misGUIEvent::SetSequenceName(string name)
{
	this->m_SequenceName = name;
}

char * misGUIEvent::GetEventName()
{
	return "Unkwon Event Name";
}
std::string misGUIEvent::GetTabName() const
{
	return m_SequenceName;
}

std::string misGUIEvent::GetSubTabName() const
{
	return m_SubTab;
}

void misGUIEvent::SetSubTab(std::string val)
{
	m_SubTab = val;
}

misGUIEvent::misGUIEvent()
{
	this->m_cascade = true;
	this->m_Proccessed = false;
	this->m_SubTab = "main";
}

void misGUIEvent::serialize(XmlSerializer& s) const
{
	try
	{
		s.serialize("Tabname", m_SequenceName);
		s.serialize("SubtabName", m_SubTab);
	}
	catch (...)
	{
		std::cout << "failed in serialize of misGUIEvent" << std::endl;
	}
}

void misGUIEvent::deserialize(XmlDeserializer& s)
{
	try
	{
		s.deserialize("Tabname", m_SequenceName);
		s.deserialize("SubtabName", m_SubTab);
	}
	catch (...)
	{
		std::cout << "failed in serialize of misGUIEvent" << std::endl;
	}
}

void misGUIEvent::operator=(const Self& right)
{
	this->m_SubTab = right.GetSubTabName();
	this->m_SequenceName = right.GetTabName();
}