#pragma once

#include "mis3DViewer.h"
#include "misNativeWindow.h" 

// The misIntegrationTestApplication class provides a base for all integration tests with services common to all of them. It 
// creates and initializes a native window, then it creates an IGSTK pulse generator. Finally calling the Run() method will create
// and start a windows message loop.
// Subclass this to test specialized functionalities of integrated modules.
class misIntegrationTestApplication
{
public:
	// Pass arguments of main to the constructor.
	misIntegrationTestApplication(int &argc, char ** argv);

	virtual ~misIntegrationTestApplication() {}

	// Starts the internally kept IGSTK pulse generator and then creates and enters the windows message loop.
	// The return value is suitable for being returned by application main().
	virtual int Run();

protected:
	typedef itk::SimpleMemberCommand< misIntegrationTestApplication > ObserverType;

	// Override this to implement behaviour that is repeated through IGSTK pulses.
	virtual void PulseHandler() {}
	
	// Gets the main window created for the test application. Can be the parent to other child windows created by the specialized 
	// test class.
	misNativeWindow GetMainWindow();

	// Callback function for the internally kept IGSTK pulse generator. Default implementation calls PulseHandler(). Make
	// sure to call base implementation when overriding.
	virtual void IgstkPulseHandler();

	//Get last received windows message
	MSG GetReceivedMessage() const;
	
private:
	int m_ArgC;
	char ** m_ArgV;

	igstk::PulseGenerator::Pointer m_PulseGenerator;
	ObserverType::Pointer m_PusleObserver;
	
	misNativeWindow m_MainWindow;   
	MSG m_ReceivedMessage;
};


