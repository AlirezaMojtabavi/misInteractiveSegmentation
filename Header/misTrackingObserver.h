#pragma once

#include "misMacros.h"

using namespace itk;

class misPolarisTrackingSubsequence;

class   misTrackingObserver :	public itk::Command
{

public:
	  typedef misTrackingObserver       Self;
	  typedef Command                   Superclass;
	  typedef SmartPointer<Self>        Pointer;
	  typedef SmartPointer<const Self>  ConstPointer;
  /** Run-time type information (and related methods). */
	  itkTypeMacro(Command,Object);
	  static  misTrackingObserver*  New();
	  misTrackingObserver(void);
	  ~misTrackingObserver(void);
	  bool IsTracking()
	  {
			return m_IsTracking;
	  }
	virtual void Execute( const itk::Object *caller, const itk::EventObject & event );
	virtual void Execute( itk::Object *caller, const itk::EventObject & event );
private:
	bool m_IsTracking;
};
