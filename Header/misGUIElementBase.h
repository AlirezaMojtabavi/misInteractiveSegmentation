#ifndef misGUIElementBase_h
#define misGUIElementBase_h

#include "misDataSetMacroes.h"
#include "misGUIElemetStruct.h"
#include "misObject.h"
#include "misPrimaeryNeededHeader.h"

class misGUIElementBase : public misOldObject
{
	//function
public:

// this macro is not contained the New function
igstkStandardClassBasicTraitsMacro( misGUIElementBase, misOldObject ) ;

static  Pointer New( string name,misGUIElementType elementType );

 virtual void 	Initilaize(void);
 virtual void   InitilaizeAll(void);

protected:
	misGUIElementBase(string name, misGUIElementType elementType);

// Variables
public:

private:
misCreateVariableWithSetGetMacro(Name,string);
misCreateVariableWithSetGetMacro(Type,misGUIElementType);
misCreateVariableWithSetGetMacro(Caption,string);
misCreateVariableWithSetGetMacro(Value,double);
misCreateVariableWithSetGetMacro(Enable,misGUIElementEnable);

};

#endif