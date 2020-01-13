#pragma once

#include "misCoreEvents.h"

class misRegistrationSequence;

class misRegistrationObserver : public itk::Command
{

	misRegistrationObserver(void);

public:
	typedef misRegistrationObserver Self;
	typedef itk::SmartPointer<Self>                       Pointer;
	typedef itk::Command                                  Superclass;
	itkNewMacro(Self);
	misRegistrationSequence* m_RegManger;


	virtual void Execute(itk::Object *caller, const itk::EventObject &event);
	//##ModelId=48049028036B
	virtual void Execute(const itk::Object *caller, const itk::EventObject &event)
	{
	}
};
