#ifndef __WindowWrapper__
#define __WindowWrapper__
//#include "misGuiWrapper.h"
using namespace System;
using namespace System::Windows;
using namespace System::Drawing;
using namespace System::Reflection;
using namespace System::Windows::Controls;
using namespace System::Windows::Markup;
using namespace System::IO;
using namespace System::Xml;
using namespace System::Threading;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Windows;
using namespace System::Windows::Data;
using namespace System::Windows::Input;
using namespace System::Windows::Interop;
using namespace System::Windows::Forms;
#include "misWindow.h"
#include "mis3DViewer.h"
#include "vcclr.h"
#include "itkcommand.h"
#include "igstkPulseGenerator.h"

#ifndef __ExternalEventDelegate__
#define __ExternalEventDelegate__
delegate void TestDelgate(misEvent* event,String^ eventname);
#endif


ref class  WindowWrapper 
{
public:
	Window^ m_window;
	System::Windows::Forms::Panel^ panel;
		System::Windows::Controls::Button^    btnClose;

	 
		delegate void InvokeDelegate(Object^ pointer);
		TestDelgate^      m_ExternalEvent;

public:
	WindowWrapper(Window^ window,String^  panleName)
	{
		this->m_window=window;
		panel=(System::Windows::Forms::Panel^)this->m_window->FindName(panleName);
				btnClose=(System::Windows::Controls::Button^ ) 		this->m_window->FindName("closeBtn");
		if(btnClose)
			btnClose->Click+= gcnew RoutedEventHandler(this,&WindowWrapper::CloseClick);


 	 



	}
	void SetExtenalEventMethod(TestDelgate^ method)
	{
		this->m_ExternalEvent+=method;
	}
 		
	void CloseClick(Object^ sender, RoutedEventArgs^ e)
		{
			exit(0);
		}

};
#endif