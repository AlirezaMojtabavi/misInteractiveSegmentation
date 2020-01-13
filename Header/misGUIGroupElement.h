
#ifndef misGUIGroupElement_h
#define misGUIGroupElement_h

#include "misPrimaeryNeededHeader.h"
#include "misGUIElementBase.h"
#include "misDataSetMacroes.h"
#include "misTypes.h"
#include "misObject.h"

typedef map    < std::string, misGUIElementBase::Pointer> misMapGroupElementList;


class misGUIGroupElement : public misOldObject
{
//Function
public:
igstkStandardClassBasicTraitsMacro( misGUIGroupElement, misOldObject ) ;
misNewMacro( misGUIGroupElement ); 


void InitializeAllGroup(void);
void SetAllElementValue(double value);
void SetAllElementActive(void);
void SetAllElementInActive(void);
void SetAllElementState(misGUIElementEnable elementState);

void AddNewElement(misGUIElementBase::Pointer pElementData);

misGUIElementBase::Pointer	GetElement(string elementName);


protected:
void	CheckNameIsUnique(void);
	    misGUIGroupElement(void);
	   ~misGUIGroupElement(void);

// Var

public:

misMapGroupElementList m_GroupList;

protected:




};



#endif