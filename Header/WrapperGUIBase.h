// WrapperGUIBase.h

#pragma once
#include "EventDelegate.h"
#include "misSoundAlertTypes.h"
#include "misEnumMessageType.h"

using namespace System;
using namespace System::Windows;
namespace WrapperGUIBase {

	public value class MessageBoxDataLog
	{
	public:

		String^ text;
		misMessageBoxType  level;
	};

	// The base class for every gui proxy communicates with core 
	public ref class GuiClientBase abstract
	{
	public:
		virtual void ProccessEvents(System::IntPtr event) = 0;
		virtual System::IntPtr GetModelDescribtion() = 0;
		virtual void ShowDialog() = 0;
		virtual void Close() = 0;
		virtual void SetAppSetting(System::IntPtr val) = 0;
		virtual void PlaySoundAlarm(misSoundAlertTypes soundData) = 0;
		virtual void ShowMessageBox(MessageBoxDataLog data) = 0;
		virtual void TakeSnapShot(String^ tabName, String^ subTabName) = 0;
		virtual void SetSnapshotFolder(String^ snapShotFolder) = 0;
		virtual void SetExtenalEventMethod(ExternalEventDelegate^ method) = 0;
		virtual System::Windows::Window^ GetMainWindow() = 0;
		virtual void TrackerIsDisconnected() = 0;
		virtual void TrackerReConnected() = 0;
	};

}
