#pragma once
#pragma once
#include "IViewerRepository.h"
#include "misLicenseStrct.h"
#include "misSubSequence.h"
#include "SubSeqNameStr.h"
class ISequenceManager;
class misGUIEvent;
class misGUIEventConvertor;

class misSolutionProperty;
class ISolutionControl  
{

public:

	virtual void ResetSolutionTotally(void) = 0;
	virtual void ResetApplication() = 0;
	virtual void SetIUDs(LicenseInformation sid) = 0;
	virtual misSubTabNameStrct	 GetLastSelectedSubTab(void) = 0;
	virtual void SetLastSelectedSubTab(misSubTabNameStrct lastSelectedSuTab) = 0;
	virtual TabAbstractStateListTypdef  GetSolutionState(void) = 0;
	virtual void UpdateLicenseForHome(std::shared_ptr<misSoftwareInformation>pSoftwareInfo) = 0;
	virtual void  PushBackNewSequence(std::shared_ptr<ISequenceManager> pSequnce, itk::Command* pcommand) = 0;
	virtual bool  DistributeEvent(misGUIEvent*  ev) = 0;
	virtual std::string FindLastSelectedSubTab(std::string  tabName) = 0;
	virtual CurrentSubSequenseStateStrct GetCurrentActiveSubSequenceStatus(void) const = 0;
	virtual std::shared_ptr<misSubSequence> FindSequnce(std::string subSequnceName) = 0;
	virtual bool UpdateLastSelectedSubTabStatus(void) = 0;
	virtual void SelectFirstTab(void) = 0;
	virtual void  AddEventToAllSubSequence(misEvent &desiredEvent, itk::Command*  observer) = 0;
	virtual std::vector<misGUIEventConvertor*> GetAllConvertors() = 0;
	virtual std::shared_ptr<misSolutionProperty> GetSoloutionProperty() const = 0;
	virtual void SetSoloutionProperty(std::shared_ptr<misSolutionProperty> val) = 0;
	virtual void CreateDelegates() = 0;
	virtual bool UpadateStatusOnHomeSelection(void) = 0;
	virtual void SelectNextSubTab(std::string currentTabName, std::string currentSubTabName) = 0;
	virtual void PulsPublish(void) = 0;
	virtual void UpdateMainMenuInGUI(const std::string& sequnec, const std::string& subSequnec) = 0;
	virtual void UpdateMainMenuInGUIByLastActiveSequence() = 0;
	virtual void UpdateSuSequebceActivity(void) = 0;
	virtual void UpdateGerenralPropertiesInGUI(void) = 0;
	virtual SubSeqNameStr GetLastActivatedSubTab() const = 0;
	virtual void SetLastActivatedSubTab(SubSeqNameStr val) = 0;
	virtual unsigned long AddObserver(const itk::EventObject & event, itk::Command *command) = 0;
	virtual void InvokeEvent(const itk::EventObject& event) = 0;
	virtual bool HasObserver(const itk::EventObject & event) const = 0;
	virtual std::shared_ptr<IViewerRepository> GetViewerRepo() const = 0;
	virtual void SetViewerRepo(std::shared_ptr<IViewerRepository> val) = 0;

};