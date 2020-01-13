#pragma once

#include "misGUIEventConvertor.h"
#include "misGuiEvent.h"

class misNavigationEventConvertor :
	public misGUIEventConvertor
{
public:
	misNavigationEventConvertor(void);
	~misNavigationEventConvertor(void);
	virtual misGUIEvent* ConvertEvents( const itk::EventObject & event );

};

