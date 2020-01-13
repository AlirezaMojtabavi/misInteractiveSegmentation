#pragma once

#include "misLicenseStrct.h"
#include "misSequenceManager.h"
#include "IPulsDistributer.h"
#include <misSoftwareInformation.h>

class misApplicationSetting;

class MISAPPBASEBEXPORTS misPulsDistributer :public IPulsDistributer
{
	

public:
	misPulsDistributer(std::shared_ptr<misSoftwareInformation> softwareInformation);
 
	void SetSeqList(sequenceListTypdef seqList);
	//List of subsequence managed directly 
	void SetIndependentSubSequenceList(const std::vector<std::shared_ptr<misSubSequence>>& subsequnecList );
	void PulsPublish(void);
	void SetLiInfo(LicenseInformation liInfo);
	void ForceUpdateInternalSDDIU(void);
	void UpdateMuteKey(void);
private:

	sequenceListTypdef m_SequenceList;
	std::vector<std::shared_ptr<misSubSequence>> m_IndependentSubsequnces;
	misApplicationSetting* m_AppSettig;
	int m_InternalCheck;
	int m_ReadedCheck;
	LicenseInformation m_SIUD;
	std::string m_InternalKey;
	std::string m_ReadedOC;
	bool m_SettedOC;
	long long int m_PulseCounter;
	bool m_ShowAs;
	void UpdateIUG(void);
	void ArfaStructuresEtanimred(void);
	void UpdateIUGRad(void);
	void UpdateIUGFos(std::string InternalLK ,std::string ReadedOC );
	bool UpdateInternalSDDIU( bool forceToUpdateKey);
	bool UpdateContinue(void);
	std::shared_ptr<misSoftwareInformation> m_SoftwareInformation = nullptr;

	
};

