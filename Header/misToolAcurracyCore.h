#pragma once
#include "misToolAccuracy.h"
 
 #include "vcclr.h"
#include "misPolarisTracker.h"
#include <msclr\gcroot.h>


using  namespace System::Windows::Threading;
using  namespace System;

 

  class misToolAcurracyInitializer
  {

	misToolAccuracy::Pointer  m_ToolAcuracy;
	gcroot<misGuiProxy^>   m_gui;
   

private:
	void ObserverMethod( itk::Object *caller, const itk::EventObject & event);
public:
	typedef misToolAcurracyInitializer  Self;
	typedef itk::MemberCommand< Self >   ObserverType;
	
	misToolAcurracyInitializer( misGuiProxy^ gui,misPolarisTracker* tracker,misToolData* tool );
	
   ~misToolAcurracyInitializer(void);

	void InitWindow(HWND  handle);

	
};

