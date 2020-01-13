#pragma once

#include "misGuiEvent.h"

class  ReadNewSolutionEvent : public misGUIEvent
{
public:
	typedef ReadNewSolutionEvent        Self;
	typedef misGUIEvent  Superclass;
	typedef std::string PayloadType;
	ReadNewSolutionEvent();
	virtual ~ReadNewSolutionEvent();
	ReadNewSolutionEvent(const Self&s);
	const std::string & Get() const;
	void Set( const std::string & _var );
	virtual char * GetEventName();
	virtual void serialize(XmlSerializer& s) const;
	virtual void deserialize(XmlDeserializer& s);
private:
	PayloadType  m_Payload;
};