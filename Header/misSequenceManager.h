#pragma once

#include "misStrctTabModel.h"
#include "misSubSequence.h"
#include "ISequenceManager.h"

class misLogger;

template < typename CST >
class ICoordinateSystemCorrelationManager;

class misTabAndSubTabName;
class misGUIEventConvertor;

class  misSequenceManager:public ISequenceManager
{
public:

 	misSequenceManager();
	void    SetMuteKe(std::string RK);
	std::string  GetTabName (void);       	
	void    SetLastActivatedSubTabName(std::string lastActivatedSubTabName );
	std::string  GetLastActivatedSubTabName(void);
	int GetNumberOfSubSequences(void);
	std::shared_ptr<misSubSequence>    GetSubSequence(int subsequenceID) override;
	std::shared_ptr<misSubSequence>    GetSubSequence(std::string subsequenceName) override;
	virtual misGUIEventConvertor*  GetGuiConvertorList()=0;
	bool RequestSelectSubTab(std::string subTabName); 
	void RequestDeselectAll(void);
	bool RequestAcitvateSubTab(std::string subTabName);
	void RequestDeAcitvateAll(void) ; 
	bool GetSelectionStatus(void)  {return this->m_TabSelected;};
	bool GetActivationStatus(void) {return this->m_TabActivated;};
	bool GetSelectedSubTabName(void)   {return this->m_TabSelected;};
	bool GetActivatedSubTabName(void)  {return this->m_TabActivated;};
	TabAbstractState               GetTabState(void);
	void UpdateCurrentSelectedSubSequenseState(void);
	CurrentSubSequenseStateStrct   GetCurrentSelectedSubSequenseState(void);
	virtual void AddCommand(itk::Command* pCommand){};
	virtual bool ProcessRequest(misGUIEvent* pEvent);
	virtual void UpdateStatus(long long int puls);
	virtual void Reset(void);
	virtual void UpdateSettingFromAppSetting(void);
	void SetDataBaseManager(std::shared_ptr<IDataBaseManager> val);
	unsigned long AddObserver(const itk::EventObject & event, itk::Command *command) override;
	void InvokeEvent(const itk::EventObject& event) override;
	bool HasObserver(const itk::EventObject & event) const override;
	void AddViewer(void *pViwer) override;
 

protected:

	void Render();
	bool RequestSelectFirstSubTab();
	std::shared_ptr< ICoordinateSystemCorrelationManager<std::string> > m_CSCorrelationManager;
		 
	misTabAndSubTabName* m_TabAndSubTabName;
	subSequenceListTypdef m_SubSequenceList;
	CurrentSubSequenseStateStrct m_CurrentSelectedSubSequence;
	bool m_TabSelected = false;
	bool m_TabActivated = true;
	std::string m_SequenceName;
	std::string m_LastActivatedSubTabName;
	std::shared_ptr<IDataBaseManager>   m_DataBaseManager;
	itk::Object::Pointer m_DummyObject = itk::Object::New();
	mutable misLogger*	m_Logger = nullptr;
};



