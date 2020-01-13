#pragma once
#include "misApplicationSetting.h"
#include "misStrctGUIModel.h"
#include "CoreProxy.h"
#include "..\misAppHelperLibrary\misAppHelperMacroes.h"
#include "misGuiProxy.h"

//a class  to connect Gui To Sequences
namespace tms
{
	class  ApplicationInitializer
	{

	protected:
		CoreProxy::Pointer		m_pCore;
		misGuiProxy<CoreProxy>*		m_GuiClient;
		misApplicationSetting*		m_appSettings;

	public:
		ApplicationInitializer(CoreProxy* core, misGuiProxy<CoreProxy>*  gui);

		void SetCore(CoreProxy * val);
		void SetGuiClient(misGuiProxy<CoreProxy>* val);
	};
}