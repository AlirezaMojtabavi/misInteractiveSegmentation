#pragma once

#include "ISubsequenceUiEventHandler.h"
#include "misAppbaseMacroes.h"
#include "misCapSetting.h"
#include "misEnums.h"
#include "misEvent.h"
#include "misGUITypes.h"
#include "misGuiEvent.h"
#include "IItkSubjectWrapper.h"
#include "misAppMacroes.h"

template <class T> class ICoordinateSystemCorrelationManager;
class IDataBaseManager;
class ISubsequenceLayout;
class misApplicationSetting;
class misSoftwareInformation;
class misTabAndSubTabName;

#pragma warning( push )
#pragma warning( disable : 4800 )

#pragma warning( pop ) 

class IGroupViewerSetting;
class ISubSequenceUIAdapter;

class MISAPPBASEBEXPORTS misSubSequence : public parcast::ISubsequenceUiEventHandler, public IItkSubjectWrapper
{
public:
	misSubSequence(std::shared_ptr<misSoftwareInformation> softwareInformation);

	itk::Object::Pointer GetDummyObject() const;
	void SetDummyObject(itk::Object::Pointer object);
	void SetCapSetting(misCapSetting capSeeting);
	void SetMuteKe(std::string RK);
	std::string GetSubTabName() const override;
	std::string GetTabName() const override;
	void SetTabName(std::string val);
	void SetSubTabName(std::string val);
	virtual bool ProcessRequest(misGUIEvent* pEvent);
	virtual void UpdateStatus(long long int puls);
	virtual void Render() = 0;
	virtual void TaskOnLeave();
	void Reset();
	virtual void UpdateSettingFromAppSetting();
	virtual void RealseAllResources() = 0;
	virtual void ResetSetting();
	virtual void OnSelected();
	virtual misEventListTypedef GetEventToGui() = 0;
	void UpdateGUIStateToGUI();
	void InvokeUiEvent(const itk::EventObject &event) override;
	void SetAllStatesList(const std::vector<std::string>& stateList) override;
	void SetSubSequenseStatusToInitlaize();
	void SetSubSequenseStatusToUnderGoingTask(
		std::string state, misResultMessageEnums resultType, std::string resultDescrpition) override;
	void SetSubSequenseStatusToCompletedTask();
	void SetSubSequenseStatusToCompletedTask(misResultMessageEnums resultType, std::string resultDescrpition);
	void RequestSelect();
	void RequestDeselect();
	void RequestAcitvate();
	void RequestDeAcitvate();
	CurrentSubSequenseStateStrct   GetCurrentSubSequenseState();
	bool GetSelectionStatus();
	bool GetActivationStatus();
	virtual  bool GetSubSeqCompletenessStatus();
	void RequestUpdateMainMenu();
	void SetDataBaseManager(std::shared_ptr<IDataBaseManager> val);
	bool HasObserver(const itk::EventObject & event) const override;
	unsigned long AddObserver(const itk::EventObject & event, itk::Command *command) override;
	void InvokeEvent(const itk::EventObject& event) override;

	std::shared_ptr<misSoftwareInformation>m_SoftwareSetting;
	misTabAndSubTabName*         m_TabAndSubTabName;
	CurrentSubSequenseStateStrct m_CurrentSubSequenseState;
	stringListTypdef m_AllStatesList;
	bool m_SubTabSelected = false;
	bool m_SubTabActivated = true;
	float m_memoryOfPRocessWhenSelect;
	float m_memoryOfProcessWhenExit;
	float m_memoryExpectToKeepOnLeave;
	std::string m_SequenceName;
	std::string m_SubsequenceName;

protected:

	bool UpdateCont();
	void SendUpdateGUIStateToGUI();

	bool m_SubTabCompleteness;
	
	std::shared_ptr<IDataBaseManager>   m_DataBaseManager;
	std::shared_ptr<ISubSequenceUIAdapter> m_UiAdpater;

private:

	bool CheckCapSetting();
	void SetInternalCap();

	misCapSetting m_CapSetting;
	double        m_InternalCap;
	std::string   m_readedKey;
	std::string   m_MuteKey;
	long long int m_TimeOnRead;
	long long int m_ExPuls;
	long long int m_EventPuls;
	int m_InternalCheck;
	int m_ReadedCheck;
	itk::Object::Pointer m_DummyObject = itk::Object::New();
	std::shared_ptr<misSoftwareInformation> m_SoftwareInformation = nullptr;

};

typedef std::vector<std::shared_ptr<misSubSequence>> subSequenceListTypdef;