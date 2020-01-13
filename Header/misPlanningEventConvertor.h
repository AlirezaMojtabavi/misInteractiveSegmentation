#pragma once

#include "misGUIEventConvertor.h"
#include "misGuiEvent.h"

class misPlanningEventConvertor: public misGUIEventConvertor
{
public:
	misPlanningEventConvertor(void);
	~misPlanningEventConvertor();
	virtual misGUIEvent* ConvertEvents( const itk::EventObject & event );
};

