#pragma once
#include "misGuiEvent.h"
#include "misEventFromGui.h"
#include "misGUIEventConvertor.h"

class misBiopsyRobotEventConvertor:public misGUIEventConvertor
{
public:
	misBiopsyRobotEventConvertor(void);
	~misBiopsyRobotEventConvertor(void);
	virtual misGUIEvent* ConvertEvents( const itk::EventObject & event );

};

