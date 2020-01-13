#pragma once

#include "serializable.h"

#define misGUIEventMacro( classname , super ) \
	/** \class classname */  \
class  classname : public super { \
public: \
	virtual char * GetEventName() { return #classname; } \
};

class misGUIEvent : public Serializable
{
public:
	typedef misGUIEvent Self;

	misGUIEvent();
	virtual ~misGUIEvent() = default;

	virtual void serialize(XmlSerializer& s) const;
	std::string GetTabName() const;
	std::string GetSubTabName() const;
	virtual char * GetEventName();
	virtual void deserialize(XmlDeserializer& s);
	void SetSequenceName(std::string name);
	void SetSubTab(std::string val);
	void operator=(const Self&);

protected:

	std::string m_SequenceName;
	std::string m_SubTab;
	bool m_cascade;
	bool m_Proccessed;
};