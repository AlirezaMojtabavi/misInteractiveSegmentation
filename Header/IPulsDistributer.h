#pragma once

#include "misLicenseStrct.h"

class IPulsDistributer
{
public:
	virtual void SetSeqList(sequenceListTypdef seqList) = 0;
 	virtual void SetIndependentSubSequenceList(const std::vector<std::shared_ptr<misSubSequence>>& subsequnecList) = 0;
	virtual void PulsPublish(void) = 0;
	virtual void SetLiInfo(LicenseInformation liInfo) = 0;
	virtual void ForceUpdateInternalSDDIU(void) = 0;
	virtual void UpdateMuteKey(void) = 0;
};
