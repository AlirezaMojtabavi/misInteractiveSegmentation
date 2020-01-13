#pragma once
#include "misApplicationSetting.h"
#include "misStrctGUIModel.h"
#include "misCoreProxy.h"
#include "..\misAppHelperLibrary\misAppHelperMacroes.h"
#include "misGuiProxy.h"

//a class  to connect Gui To Sequences
class  misApplicationInitializer
{

protected:
	ICoreProxy* m_pCore;
	misGuiProxy<ICoreProxy>*		m_GuiClient ;
	misApplicationSetting*		m_appSettings;

public:
	misApplicationInitializer(ICoreProxy* core,misGuiProxy<ICoreProxy>*  gui);

	void SetCore(ICoreProxy * val);
	void SetGuiClient(misGuiProxy<ICoreProxy>* val);
};

