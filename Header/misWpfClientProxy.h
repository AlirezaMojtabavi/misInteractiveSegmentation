#pragma once
#include "misGuiProxy.h"
 


template <typename  CoreType>
class misWpfClientProxy :
	public misGuiProxy<CoreType>
{
protected :

	gcroot<::misTakeSnapShot^>           m_SnapShotManger;
	gcroot<WrapperGUIBase::ExternalEventDelegate^>      m_ExternalEvent;
	misTabAndSubTabName*               m_TabAndSubTabName;  
	gcroot<misSoundMessagePlayer^>   m_MessagePlayer;
	
	gcroot<WrapperGUIBase::GuiClientBase^> gui;
public:

	WrapperGUIBase::GuiClientBase^ GetGui()
	{
		return gui;
	}
	void SetGui( WrapperGUIBase::GuiClientBase^ exGUi )
	{
		gui = exGUi;

	}
	~misWpfClientProxy(void);
	bool ProccessEvents( misGUIEvent* pEvent )

	{
		System::IntPtr   eventPtr(pEvent);
		gui->ProccessEvents(eventPtr);
		return true;
	}


	

	misStrctGUIModel* GetModelDescribtion()
	{
		System::IntPtr  modelPointer = gui->GetModelDescribtion();
		misStrctGUIModel* model =(misStrctGUIModel*)(modelPointer.ToPointer());
		return model;
	}

	void ShowDialog()
	{
		gui->ShowDialog();
	}

 
	void Show()
	{
		gui->Show();
	}

	void Close()
	{
		gui->Close();

	}

	void TakeSnapShot( std::string tabName, std::string subTabName )
	{
		System::String^ tabbanmeClr=gcnew System::String(tabName.c_str());
		System::String^ subtabbanmeClr=gcnew System::String(subTabName.c_str());
		gui->TakeSnapShot(tabbanmeClr,subtabbanmeClr);

	}

	void ShowMessageBox( NativeLogMessageBoxData messageData )
	{
		WrapperGUIBase::MessageBoxDataLog manageddata;
		manageddata.text = gcnew  String(messageData.message.c_str());

		if (messageData.level == DEBUGLOGGING || messageData.level == INFO || messageData.level == MUSTFLUSH || 
			messageData.level == NOTSET)
			manageddata.level = static_cast<WrapperGUIBase::misMessageBoxType>(WrapperGUIBase::misMessageBoxType::Information); 
		else if (messageData.level == CRITICAL || messageData.level == FATAL)
			manageddata.level = static_cast<WrapperGUIBase::misMessageBoxType>(WrapperGUIBase::misMessageBoxType::Error); 
		else if(messageData.level == WARNING)
			manageddata.level = static_cast<WrapperGUIBase::misMessageBoxType>(WrapperGUIBase::misMessageBoxType::Warning); 
		gui->ShowMessageBox(manageddata);
	}

	void PlaySoundAlarm( misSoundAlertTypesNative soundData )
	{
		WrapperGUIBase::misSoundAlertTypes soundDataM  = static_cast<WrapperGUIBase::misSoundAlertTypes>(soundData);
		gui->PlaySoundAlarm(soundDataM);

	}

	void SetAppSetting( System::IntPtr val )
	{
		gui->SetAppSetting(val);
	}
	
	void SetExtenalEventMethod(CoreType* object, CallBackDelegate callBack) 
	{
	 
		misGuiDispathcer^ guiDispatcher=gcnew misGuiDispathcer(object);
		WrapperGUIBase::ExternalEventDelegate^ method =gcnew WrapperGUIBase::ExternalEventDelegate(guiDispatcher, 
			&misGuiDispathcer::CaptureEvent); 

		gui->SetExtenalEventMethod(method);

	}

	virtual  void SetSnapshotFolder(std::string snapShotFolder)
	{
		gui->SetSnapshotFolder(gcnew String(snapShotFolder.c_str()));

	}
	


	virtual void TrackerIsDisconnected() override
	{
		gui->TrackerIsDisconnected();
	}
	virtual void TrackerReConnected() override
	{
		gui->TrackerReConnected();
	}
};

