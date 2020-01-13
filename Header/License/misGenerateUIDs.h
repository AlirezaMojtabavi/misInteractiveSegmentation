#pragma once

#include "misHardwareIdentity.h"
#include "misLicenseStrct.h"
#include "misOSIdentity.h"

class    misGenerateUIDs
{
private:
	void UpdateUIDs(void);
	misUIDForLicenseStrct m_UIDsInfo;
	void GetUIdsInfo( misUIDForLicenseStrct &UIDInfo,int it /*= true*/);

public:
	misGenerateUIDs(void);
	~misGenerateUIDs(void);

	misUIDForLicenseStrct GetUIdsInfo( int dob /*= true*/);	
	
};

