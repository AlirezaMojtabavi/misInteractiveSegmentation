//mehdi
#pragma once

#include "misDataProcedure.h" 
#include "misDataProcedureEvents.h"
#include "misGuiEvent.h"
#include "misStrcts.h"

class __declspec( dllexport )  misDataProcedureObserver :
	public itk::Command
{
private:
	igstk::Object*  m_parent;
 	
public:
	
	misSetMacro(parent,igstk::Object*);

  typedef misDataProcedureObserver  Self;
  typedef itk::SmartPointer<Self>                    Pointer;
  typedef itk::Command                               Superclass;
static Pointer New(void)  
{  
  Pointer smartPtr = ::itk::ObjectFactory<Self>::Create();  
  if(smartPtr.GetPointer() == NULL) 
    {  
	    smartPtr = new Self;  
    }  
	smartPtr->UnRegister(); 
  return smartPtr;  
}  
  

  void Execute( const itk::Object *caller, const itk::EventObject & event )
    {

    }
  void Execute( itk::Object *caller, const itk::EventObject & event )
  {
	  
	  misDataSequence* dataProc=dynamic_cast<misDataSequence*>(caller);


	  // TODO: check JHB seems not necessary

	//if ((typeid(event)==typeid(misDicomTreeListEvent)))
	//{
	//		misDataSequence* dataProcedure=dynamic_cast<misDataSequence*>(caller);
	//		this->InvokeEvent(event);
	//		//dataProcedure->RequestSetCorrelationWindow();
	//}

	//if ((typeid(event)==typeid(misSetGUIState)))
	//{
	//	misDataSequence* dataProcedure=dynamic_cast<misDataSequence*>(caller);
	//	this->InvokeEvent(event);
	//	//dataProcedure->RequestSetCorrelationWindow();
	//}
	 
 
    } 
  



 
  
};
