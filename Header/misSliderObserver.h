#pragma once
#include "itkCommand.h"

#include "misCoreEvents.h"
class mis3DViewer;
using namespace itk;


class misSliderObserver:public itk::Command
{
private:	
	misSliderObserver(void)
	{

	};

public:
	typedef misSliderObserver   Self;
	typedef itk::SmartPointer<Self>    Pointer;
	mis3DViewer*   m_HViewer;
	//      itk::Command                            Superclass;
	itkNewMacro(Self);
	//##ModelId=4804901D03D8
	virtual void Execute(itk::Object *caller, const itk::EventObject &event);
	//##ModelId=48049028036B
	virtual void Execute(const itk::Object *caller, const itk::EventObject &event);

};
