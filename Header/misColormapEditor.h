#pragma once
#include "misSubsequenceGUIWrapper.h"
#include "misGuiEvent.h"

ref class misColormapEditor : public misSubsequenceGUIWrapper
{
public:
	misColormapEditor(String^ tabName, String^ subTabName);
	virtual void ApplyRequestToGUI(misGUIEvent*  pEvent) override;

	//modeifier
	virtual void SetExtenalEventMethod(WrapperGUIBase::ExternalEventDelegate^ method) override;
	virtual void UpdateSettingFromAppSetting() override;
	void ShowDialog();

	GUILibraryAnimal::Forms::misColorMapEditor^ m_mainWindow;

	virtual misRendererLibraryWrapperGUI^ GetRenderPackage() override;


	System::Collections::ArrayList^ GetLastPoints();
	void SetLastPoints(System::Collections::ArrayList^ val);
	System::Collections::ArrayList^ GetLastLoadedImageHistogram();
	void SetLastLoadedImageHistogram(System::Collections::ArrayList^ val);
	System::Collections::ArrayList^ GetLastLoadedImageRange();
	void SetLastLoadedImageRange(System::Collections::ArrayList^ val);
protected:
	virtual  void MappingEvents() override;



	void Onupdated(System::Object ^sender, GUILibraryAnimal::VoreenDataUpdateEventArgs ^e);


	virtual System::Windows::Window^ get_mainWindow() override;


	virtual System::Windows::Controls::UserControl^ getUserControl() override;

	System::Collections::ArrayList^ m_LastPoints;
	System::Collections::ArrayList^ m_LastLoadedImageHistogram;
	System::Collections::ArrayList^ m_LastLoadedImageRange;

};

