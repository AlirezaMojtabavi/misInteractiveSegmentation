#pragma once

#include "misWindow.h"

class misModelObserver:public itk::Command
	  {
	  public:

		  igstkStandardClassBasicTraitsMacro( misModelObserver, itk::Command ) ;
		  igstkNewMacro( Self );
		  misWindow*  m_ActiovWindow;

			  virtual void Execute(itk::Object *caller, const itk::EventObject &event)
			  {
				  if (typeid(event)==typeid(misWindowsActivatedEvent))
				  {
					  misWindow*  p=dynamic_cast<misWindow*>(caller);
					  if (p)
						  this->m_ActiovWindow=p;
				  }
			  }
			//##ModelId=48049028036B
			  virtual void Execute(const itk::Object *caller, const itk::EventObject &event)
			  {
			  }

			  misModelObserver()
			  {
				  m_ActiovWindow = 0;
			  };
	  };
