#pragma once

#include "SubSeqNameStr.h"
#include "mis3DViewer.h"
#include "misApplicationSetting.h"
#include "misEvent.h"
#include "misGUITypes.h"
#include "misLicenseStrct.h"
#include "misLogger.h"
#include "misObject.h"
#include "misSequenceManager.h"
#include "misSolutionProperty.h"
#include "IViewerRepository.h"
#include "misUpadateTabStateAbstract.h"
#include "misSolutionControlGuiAdapter.h"
#include "misSequenceChanger.h"
#include "ISolutionControl.h"
#include "misViewerRepository.h"
#include <misSoftwareInformation.h>


class vtkTimerLog;
class misDataBaseManager;
class misDatasetManager;
class misTabAndSubTabName;
class misSequencesObserver;
class misSequenceOrders;
class ITabAndSubTabActicationControl;
class misApplicationSetting;
class misPulsDistributer;
class mis3DVolumeRenderer;



class misSolutionControl : public ISolutionControl
{

public:

	misSolutionControl(std::shared_ptr<ITabAndSubTabActicationControl> sequnecActivationOrder, std::shared_ptr<misSoftwareInformation> softwareInformation);

	misPrivateBooleanVariableWithPublicAccessorsMacro(m_UseTheardTest, UseTheardTest);
	void ResetSolutionTotally(void);
	void SetIUDs(LicenseInformation sid);
	misSubTabNameStrct	 GetLastSelectedSubTab(void);
	void            	 SetLastSelectedSubTab(misSubTabNameStrct lastSelectedSuTab);
	TabAbstractStateListTypdef  GetSolutionState(void);
	void UpdateLicenseForHome(std::shared_ptr<misSoftwareInformation> pSoftwareInfo);
	void  PushBackNewSequence(std::shared_ptr<ISequenceManager> pSequnce,itk::Command* pcommand);

	bool  DistributeEvent(misGUIEvent*  ev);

	void ResetApplication() override;

	void LeaveSequence();

	std::string                  FindLastSelectedSubTab(std::string  tabName);
	CurrentSubSequenseStateStrct GetCurrentActiveSubSequenceStatus(void) const { return this->m_CurrentSelectedSubSequence;};
	std::shared_ptr<misSubSequence> FindSequnce(std::string subSequnceName);
	bool UpdateLastSelectedSubTabStatus(void);
	 
	void SelectFirstTab(void);
	void  AddEventToAllSubSequence(misEvent &desiredEvent, itk::Command*  observer);
	std::vector<misGUIEventConvertor*> GetAllConvertors();
	 


	std::shared_ptr<misSolutionProperty> GetSoloutionProperty() const;
	void SetSoloutionProperty(std::shared_ptr<misSolutionProperty> val);

	void CreateDelegates();

	bool UpadateStatusOnHomeSelection(void);

 
	void SelectNextSubTab  ( std::string currentTabName, std::string currentSubTabName );
	
	void PulsPublish(void);
	void UpdateMainMenuInGUI(const std::string& sequnec, const std::string& subSequnec);
	void UpdateSuSequebceActivity(void);

	void UpdateMainMenuInGUIByLastActiveSequence() override;

	void UpdateGerenralPropertiesInGUI(void);


 
	SubSeqNameStr GetLastActivatedSubTab() const;
	void SetLastActivatedSubTab(SubSeqNameStr val);

	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *command) override;


	virtual void InvokeEvent(const itk::EventObject& event) override;


	virtual bool HasObserver(const itk::EventObject & event) const override;

	std::shared_ptr<IViewerRepository> GetViewerRepo() const override;
	void SetViewerRepo(std::shared_ptr<IViewerRepository> val) override;
protected:

	void SetSolutionState(TabAbstractStateListTypdef lastSavedSolutionState);
	void SetCurrentActiveSubSequenceStatuset(CurrentSubSequenseStateStrct currentSubSequenseState);
	void SetNextStatus(SubSeqNameStr seqNameStr , bool activationStatus);
	void SelectBeforeSubTab( std::string currentTabName, std::string currentSubTabName );

private:


	void ResetAllTabs(void);
	bool SubTabSelectionChanged(SubSeqNameStr newSelectedName);
	void TabSelectionChanged   (    std::string tabName);
	   bool InternalDistributeEvent( misGUIEvent* pEvent );
	bool RequestSelectPreviousSubSequence(void);
	
	std::shared_ptr<misPulsDistributer> m_PulsDistributer;
	misDatasetManager*                 m_DatasetManager;
	misApplicationSetting*             m_AppSettings;
    misSequenceOrders*            m_SequenceOrders;
	misTabAndSubTabName* m_TabAndSubTabName;
	CurrentSubSequenseStateStrct  m_CurrentSelectedSubSequence;
	SubSeqNameStr m_LastActivatedSubTab;
	SubSeqNameStr m_PreviousActivatedSubTab;
	sequenceListTypdef  m_SequenceList;
	bool m_LoggDetailStates;

	std::shared_ptr<ITabAndSubTabActicationControl>  m_ActivationControler;
	std::unique_ptr<misSequenceChanger> m_SequenceChanger;
	std::shared_ptr<misSolutionProperty> m_SoloutionProperty;
	std::shared_ptr<misUpadateTabStateAbstract>  m_UpadateTabStateAbstract;
	std::shared_ptr<misSolutionControlGuiAdapter> m_SolutionUiAdapter;
	itk::Object::Pointer m_DummySubject = itk::Object::New();
	std::shared_ptr<IViewerRepository> m_ViewerRepo = std::make_shared<misViewerRepository>();
};
