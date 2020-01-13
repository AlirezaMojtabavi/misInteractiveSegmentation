#pragma once


#define misLoadedEventMacro( classname, superclass, payloadtype ) \
class  classname : public superclass \
{ \
public:  \
	typedef classname        Self; \
	typedef superclass  Superclass; \
	typedef payloadtype PayloadType; \
	classname() {} \
	virtual ~classname() {} \
	classname(const Self&s) :superclass(s){}; \
	const PayloadType & Get() const \
{ return m_Payload; }  \
	void Set( const payloadtype & _var ) \
{ m_Payload = _var; }  \
	virtual char * GetEventName() { return #classname; } \
private: \
	PayloadType  m_Payload; \
};