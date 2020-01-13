#pragma once
#include "misApplicationSetting.h"
#include "misTabAndSubTabName.h"
#include "ModelStruct.h"
#include "misStrctGUIModel.h"
#include "misGuiEvent.h"
#include "misSoundAlertTypesNative.h"
#include "NativeLogMessageBoxData.h"

 


template <typename  CoreType>
class misGuiProxy 
{

public:
	//misGUIEvent* event,String^ eventname
	 
	typedef  bool  (CoreType::*CallBackDelegate)(misGUIEvent* );
		 
	virtual bool ProccessEvents(misGUIEvent* pEvent)=0;
	virtual misStrctGUIModel* GetModelDescribtion()=0;
	virtual  void ShowDialog()=0;
	virtual  void Close()=0;
	virtual  void SetSnapshotFolder(std::string snapShotFolder)=0;
	virtual void TakeSnapShot( std::string tabName, std::string subTabName)=0;
	virtual void PlaySoundAlarm( misSoundAlertTypesNative soundData )=0;
	virtual void         ShowMessageBox(NativeLogMessageBoxData data)=0;
	virtual void SetExtenalEventMethod(CoreType* object, CallBackDelegate callBack)=0;
	virtual void TrackerIsDisconnected() = 0;
	virtual void TrackerReConnected() = 0;
};

 