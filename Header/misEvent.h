#pragma once

#include "misLibraryMacroes.h"

class misOldObject;
 
class  misEvent: public itk::EventObject
{
public:
	typedef misEvent Self;
	typedef EventObject Superclass;

	misEvent( );
	//misEvent( misOldObject* pObject);

	virtual ~misEvent(); ;
	virtual const char * GetEventName() const;
	virtual bool CheckEvent(const ::itk::EventObject* e) const;
	virtual ::itk::EventObject* MakeObject() const;

	misEvent(const Self &s) :EventObject(s){};

	std::string GetTabName()    const;
	std::string GetSubTabName() const;
	void SetSequenceName(std::string name);
	void SetSubTab(std::string val);
	bool IsProccessed() const;
	void SetProccessing(bool val);
	void operator=(const Self&);
protected:

	std::string  m_SequenceName;
	std::string  m_SubTab;
	bool    m_cascade;//sen to other tab or processes by core observer
	bool    m_Proccessed;
};

typedef std::vector<misEvent*> misEventListTypedef;