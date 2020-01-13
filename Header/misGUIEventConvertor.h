#pragma once

#include "misGuiEvent.h"
#include "misAppbaseMacroes.h"

class MISAPPBASEBEXPORTS misGUIEventConvertor
{
public:
	misGUIEventConvertor();
	~misGUIEventConvertor();
	virtual misGUIEvent* ConvertEvents( const itk::EventObject & event )=0;
};