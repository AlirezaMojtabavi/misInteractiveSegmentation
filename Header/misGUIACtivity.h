#pragma once
#include "misApplicationSetting.h"
#include "../WrapperGuiDll/SequnecsButtons.h"


class misTabAndSubTabName;

struct TabAbstractState;
typedef std::vector<TabAbstractState> TabAbstractStateListTypdef;

public ref class misGUIACtivity
{
public:
	misGUIACtivity(TabAbstractStateListTypdef* tabAndSubTabStates, GUILibrary::misWpfClientGui^ mainWindow, SequnecsButtons^);
	void Method_misButton_SnapShotViewer(String^ patientStrName, String^ patientStrAge,
		String^ patientStrSex, String^ solutionPath);
	void Method_misButton_Home();
	void Method_misButton_TrackingActivation();
	void UpdateGUIMainMenu(String^ sequnceName, String^ subsequenceName);

private:

	void ActiveDataUploading();
	void ActiveLandamrkSelction();
	void ActivateDataChecking();
	void Method_misButton_ImageCorrelation();
	void Method_misButton_Create3DModel();
	void Method_misButton_CreateCompositeModel();
	void Method_misButton_Planning();
	void Method_misButton_LandmarkRegistration();
	void Method_misButton_SurfaceRegistration();
	void Method_misButton_Navigation();
	void UpdateHomeGUIMenu(TabAbstractState tabState);
	void UpdateDataMangerGUIMenu(TabAbstractState tabState);
	void UpdateAnalysisStudioGUIMenu(TabAbstractState tabState);
	void UpdatePlanningGUIMenu(TabAbstractState tabState);
	void UpdateRegistrationGUIMenu(TabAbstractState tabState);
	void UpdateTrackingGUIMenu(TabAbstractState tabState);
	void UpdateLandmarkSelectionGUIMenu(TabAbstractState tabState);
	void UpdateNavigationGUIMenu(TabAbstractState tabState);
	void UpdateSnapShotGUIMenu(TabAbstractState  tabState);
	void SetExtenalEventMethod(WrapperGUIBase::ExternalEventDelegate^ method);
	void RefreshGUI();
	SequnecsButtons^ m_Buttons;
	TabAbstractStateListTypdef* m_TabAndSubTabStates;
	misTabAndSubTabName* m_TabAndSubTabName;
	GUILibrary::misWpfClientGui^ m_MainWindow;
	WrapperGUIBase::ExternalEventDelegate^ m_ExternalEvent;
	misApplicationSetting* m_AppSetting;
	const bool m_PlanningStation = misApplicationSetting::GetInstance()->GetGUISetting().PPSA;
};