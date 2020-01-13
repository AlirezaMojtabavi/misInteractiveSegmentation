#pragma once

#include "misGuiEvent.h"

class  misDataSelectionPackageDataSelectedEvent : public misGUIEvent
{
public:
	typedef misDataSelectionPackageDataSelectedEvent        Self;
	typedef misGUIEvent  Superclass;
	typedef std::string PayloadType;
	misDataSelectionPackageDataSelectedEvent();
	virtual ~misDataSelectionPackageDataSelectedEvent();
	misDataSelectionPackageDataSelectedEvent(const Self&s);;
	const std::string & Get() const;
	void Set( const std::string & _var );
	virtual char * GetEventName();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
private:
	PayloadType  m_Payload;
};