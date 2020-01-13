#include "misGuiEvent.h"
using namespace System;;
ref class misGuiToolDispathcer
{

public:

	misToolAccuracy* m_Core;

	misGuiToolDispathcer(misToolAccuracy* pCore)
	{
		m_Core=pCore;

		 

	}


	void CaptureEvent(misGUIEvent* event,String^ eventname)
	{
		System::Diagnostics::Debug::WriteLine(eventname);
		//if  it possible to get event data in .net data structure and  convert it to its equivalent c++ dats structure 
		//temp
		m_Core->ProccessEvents(event);
	}
};
