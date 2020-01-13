#pragma once
#include "igstkObject.h"
#include "itkEventObject.h"

template <class T>
class misAction
{
private:
	itk::EventObject*  m_Event;
public:
	itk::EventObject* GetEvent() const { return m_Event; }

	misAction(itk::EventObject*  pEvent)
	{
		m_Event=pEvent;
	}
	typedef  void (T::*TMemberFunctionPointer)( const itk::EventObject & event );

	void SetCallbackFunction(T* object,  
		TMemberFunctionPointer memberFunction)
		{
			m_This = object;
			m_MemberFunction = memberFunction;
	}

	void Execute( const itk::EventObject & event )
	{
		if( m_MemberFunction ) 
		{
			((*m_This).*(m_MemberFunction))(event);
		}
	}
	//	typedef  void (T::*TMemberFunctionPointer)(Object*, const EventObject &);
	T* m_This;
	TMemberFunctionPointer m_MemberFunction;
public:

};
