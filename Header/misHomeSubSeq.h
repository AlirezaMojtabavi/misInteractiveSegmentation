#pragma once

#include "misSubSequence.h"
#include <ILicenseTimeValidator.h>

class misDatasetManager;
class misDataBaseManager;

class misHomeSubSeq : public misSubSequence
{
public:
	misHomeSubSeq(std::shared_ptr<misSoftwareInformation> softwareInformation);
	void InitialeGuiProcessing();
	void UpdateStatus(long long int puls);
	void TaskOnLeave(void);
	void UpdateSettingFromAppSetting(void);
	void RealseAllResources();
	void Render();
	void OnSelected(void);
	bool ProcessRequest( misGUIEvent* pEvent );
	misEventListTypedef GetEventToGui();
	std::string GetSoloutionUID() const { return m_SoloutionUID; }
	void SetSoloutionUID(std::string val);
private:


	void CheckDatabaseConnectivity(void);
	void TryToConnectToDataBase(void);
	void UpadateSolutionList(void);
	void OpenWaitingBar(void);
	void CloseWaitingBar(void);	
	bool                   m_ValidLicense;
	bool                   m_DataBaseStatus;
	int                    m_TryToConnectDataDatabase;
	int                    m_MaxTryToConnectDataDatabase;
	std::string m_SoloutionUID;
	parcast::LicenceTimeState m_TimedLicenseState;
	SYSTEMTIME m_TimeRemainingLicense;
};

