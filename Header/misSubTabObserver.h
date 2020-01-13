#pragma once

#include "misCoreEvents.h"
#include "misWindow.h"

class misStrctGUIModel;

class misSubTabObserver:public itk::Command
{
public:
	misSubTabObserver(void);
	typedef misSubTabObserver   Self;
	typedef itk::SmartPointer<Self>    Pointer;
	misWindow::Pointer   m_window;
	//      itk::Command                            Superclass;
	itkNewMacro(Self);
	//##ModelId=4804901D03D8
	virtual void Execute(itk::Object *caller, const itk::EventObject &event) ;
	//##ModelId=48049028036B
	virtual void Execute(const itk::Object *caller, const itk::EventObject &event)  ;
};
