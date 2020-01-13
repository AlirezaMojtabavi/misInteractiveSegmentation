#pragma once

#include "misGUIEventConvertor.h"

class misTrackingProcedureEventConvertor :
	public misGUIEventConvertor
{
public:
	misTrackingProcedureEventConvertor(void);
	~misTrackingProcedureEventConvertor(void);
	virtual misGUIEvent* ConvertEvents( const itk::EventObject & event) ;

};

