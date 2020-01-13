#ifndef _MISPROGRESSBARGUI
#define _MISPROGRESSBARGUI

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Threading;
using namespace System::Windows::Threading;
using namespace System::Windows::Markup;
using namespace System::Windows::Interop;
using  namespace  System::Windows::Threading;
public ref class misProgressBarGUI
{

private :
	
	#ifdef _DEBUG
	
	GUIElement::Forms::misProgressBarDebug^ m_ProgressWindow;
	
	#else

	GUIElement::misProgressBar^ m_ProgressWindow;

	#endif



	System::Threading::Thread^ m_ShowThread;
	String^ m_LastCancelCallbackFunction;
	String^ StatusText;
	String^ TitleText;

	bool m_IsInShowing;
	bool m_RequstForFinish;
	bool m_autoUpdateMode;	
	delegate void CloseProgressDelegate(void);
	delegate void ShowProgressDelegate(void);

	void  ShowProgressWindow();
	void  CloseProgressWindow();
	void  ThraedStart();
	void  ProgressWindow_Activated(System::Object^ sender,System::EventArgs^ arg);
	void  ProgressWindow_Closed( System::Object^ sender,System::EventArgs^ arg );
	
	System::Windows::Input::MouseButtonEventHandler^ m_cancelEventDelegate;

	 Mutex^ m_mutex;


	 // jhb
	// AutoResetEvent^ m_waitHandles;
	 




	
public:	
    misProgressBarGUI( );

	void  Start();
	void  Finish();

	void  UpdateProgress(double progressValue);
	void  UpdateProgressText(String^ progressStatusText);

	void  SetText(String^ title, String^ status);
	void  SetAutomaticModeStatus(bool val);
	void  SetCancelEvent(System::Windows::Input::MouseButtonEventHandler^ ev );
	void  SetLastCancelCallbackFunction(String^ lastCancelFunction);

	String^ GetLastCancelCallbackFunctionName( void);
	
};

#endif
