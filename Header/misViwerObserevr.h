#pragma once
#ifndef __misViwerObserevr__
#define __misViwerObserevr__
#include "misHeader.h"

#include "itkCommand.h"
class misGoupViewerFourViwer;



//obserevs  selct point
class    misViwerObserevr:public itk::Command
{

public:

	typedef misViwerObserevr   Self;
	typedef itk::SmartPointer<Self>                 Pointer;
	//      itk::Command                            Superclass;
	itkNewMacro(Self);
	misGoupViewerFourViwer*  m_RegPrep;


	virtual void Execute( const itk::Object *caller, const itk::EventObject & event )
	{

	}
	virtual void Execute( itk::Object *caller, const itk::EventObject & event );
};
#endif