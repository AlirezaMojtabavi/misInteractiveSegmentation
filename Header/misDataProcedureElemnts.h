#pragma once
#include "misGUIGroupElement.h"

class misDataProcedureElemnts :
	public misGUIGroupElement
{
public:
	igstkStandardClassBasicTraitsMacro( misDataProcedureElemnts,misGUIGroupElement) ;
	igstkNewMacro( misDataProcedureElemnts ); 

	misDataProcedureElemnts(void);
	void SetInitialState()
	{
	}
public:
	~misDataProcedureElemnts(void);
};
