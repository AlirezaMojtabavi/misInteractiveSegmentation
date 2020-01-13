#ifndef _MISTESTWINDOW
#define _MISTESTWINDOW

 

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;
using namespace System::Windows;



public ref class misTestWindow : public misGuiWrapper
{

private:

	void misButton_Exit_MouseLeftButtonUp(System::Object^ sender,System::Windows::Input::MouseButtonEventArgs^ arg);

public:

	 
	virtual void MappingEvents()override;

	GUILibrary::misTestWindow^ m_mainWindow;
	misTestWindow(GUILibrary::misTestWindow^  window);

};


#endif